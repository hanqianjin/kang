#if __linux__
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <linux/netlink.h>
#include <stdio.h>


#include<sys/types.h>
#include<fcntl.h>
#endif
#include <QLoggingCategory>
#include <QSocketNotifier>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QMutexLocker>
#include <QProcess>
#include "HotplugWatcher.h"

#define	REMOUNT_OVERTIME	(60*1000)
#define	FSCK_WAIT_TIME		(1000)

HotplugWatcher::HotplugWatcher(QObject *parent)
	: QObject(parent)
	, m_notifier(NULL)
{
	removeMountPath();
	qintptr fd = initialize();
	if (fd >= 0) 
	{
		m_notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
		connect(m_notifier, SIGNAL(activated(int)), this, SLOT(slotReadyRead()));
	}
}

void HotplugWatcher::slotReadyRead()
{
#if __linux__
	QByteArray data;
	data.resize(4096);
	size_t len = ::read(m_notifier->socket(), data.data(), 4096);
	data.resize(len);
	data = data.replace(0, '\n').trimmed();

	QTextStream out(&data);
	QString brif = out.readLine();
	QMap<QString, QString> attrList;
	while (!out.atEnd()) 
	{
		QString line = out.readLine();
		QStringList arr = line.split('=', QString::SkipEmptyParts);
		if (arr.size() == 2) 
		{
			attrList.insert(arr[0], arr[1]);
		}
	}

	QString subSystem = attrList["SUBSYSTEM"];
	if(subSystem == "usbtmc_gadget")
	  {
	    QString outstr = attrList["miniusb"];
	    if(outstr == "plug-out")
	      {
		  emit sigtmcUsbDeviceRemoved();
		//QMessageBox::about(0,"scpi",attrList["DEVNAME"] + ";" + outstr + ";" + brif);
	      }
	  }
	else if (subSystem == "usb")
	{
		QString devType = attrList["DEVTYPE"];
		QString action = attrList["ACTION"];
		if (devType == "usb_device") 
		{
			if (action == "add") 
			{
				emit sigUsbDeviceAdded();
			}
			else if (action == "remove") 
			{
				emit sigUsbDeviceRemoved();
			}
			else if (action == "change") 
			{
				emit sigUsbDeviceChanged();
			}
		}
	}
	else if (subSystem == "mmc") 
	{
		QString action = attrList["ACTION"];
		if (action == "add") 
		{
			emit sigMmcDeviceAdded();
		}
		else if (action == "remove") 
		{
			emit sigMmcDeviceRemoved();
		}
		else if (action == "change") 
		{
			emit sigMmcDeviceChanged();
		}
	}
	else if (subSystem == "block") 
	{
		QString devType = attrList["DEVTYPE"];
		if (devType == "partition") 
		{
			QString action = attrList["ACTION"];
			QString node = "/dev/" + attrList["DEVNAME"];
			if (brif.contains("usb")) 
			{
				emit sigUsbStorageUpdated(action, node);
			}
 			else if (brif.contains("mmc")) 
 			{
// 				if (action.contains("add"))
// 				{
// 					node = "dev//dev/mmcblk1p1";
// 					emit sigMmcStorageUpdated(action, node);
// 					node = "dev//dev/mmcblk1p2";
// 					emit sigMmcStorageUpdated(action, node);
// 
// 				}
// 				else
// 				{
					emit sigMmcStorageUpdated(action, node);
	//			}
				
			}
		}
	}
#endif
}

int HotplugWatcher::initialize()
{
#if __linux__
	const int buffersize = 16 * 1024 * 1024;

	struct sockaddr_nl snl;
	::memset(&snl, 0, sizeof(struct sockaddr_nl));
	snl.nl_family = AF_NETLINK;
	snl.nl_groups = 1;

	int monitor_fd = ::socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
	if (monitor_fd < 0) 
	{
		qWarning("error getting socket: %s", strerror(errno));
		return -1;
	}

	::setsockopt(monitor_fd, SOL_SOCKET, SO_RCVBUFFORCE, &buffersize, sizeof(buffersize));
	int retval = ::bind(monitor_fd, (struct sockaddr*) &snl, sizeof(struct sockaddr_nl));
	if (retval < 0) 
	{
		qWarning("bind failed: %s", strerror(errno));
		::close(monitor_fd);
		return -1;
	}

	struct sockaddr_nl _snl;
	socklen_t _addrlen = sizeof(struct sockaddr_nl);
	retval = ::getsockname(monitor_fd, (struct sockaddr *)&_snl, &_addrlen);
	if (retval == 0) 
	{
		snl.nl_pid = _snl.nl_pid;
	}

	return monitor_fd;
#else
	return 0;
#endif
}

/**
* @brief: 删除挂载点路径
* @return: void
*/
void HotplugWatcher::removeMountPath()
{
	QDir dir;
	dir.rmpath(QString(SD_PATH));
    dir.rmpath(QString(USB_PATH_1));
}

HotplugDevice::HotplugDevice(Media_Type type, QObject *parent)
	: QObject(parent)
	, m_medium(type)
{
	m_pTimer = new QTimer(this);
	connect(m_pTimer, &QTimer::timeout, this, &HotplugDevice::onTimerOut);
	m_pTimer->setSingleShot(true);
	m_pTimer->setInterval(REMOUNT_OVERTIME);
	if (type == Type_USB) {
        QFileInfo info(USB_PATH_1);
		m_node = info.absolutePath();
	}
	else if (type == Type_SD) {
		QFileInfo info(SD_PATH);
		m_node = info.absolutePath();
	}
	else {
		m_node = QDir::tempPath() + "/f270/";
	}
	init();
}

void HotplugDevice::onTimerOut()
{
	if (!addDevice(m_remountPath))
	{
		emit mediaConnectedFail();
	}
}

bool HotplugDevice::isExist()
{
	return m_valid;
}

bool HotplugDevice::isExistDev()
{
    if(m_dev.isEmpty())
    {
        return false;
    }
    QProcess process;
    process.start("fdisk -l");
    process.waitForFinished();
    process.readLine();
    QString data;

    while (!process.atEnd())
    {
       data = process.readLine();
      if(data.contains(m_dev))
      {
          return true;
      }
    }
    return false;
}

bool HotplugDevice::addDevice(QString dev)
{
	if (m_valid) {
		return false;
	}

	if (isMount()) {
		umount();
	}

	int ret = mount(dev, "vfat");
	if (ret == 22) {
		ret = mount(dev, "ntfs");
	}

	if (ret == 0) {
		m_dev = dev;
		reset();
		return m_valid;
	}

	qDebug() << "Mount Error - " << m_dev << dev;
	qDebug() << "Mount Error - " << errno << strerror(errno);
	return false;
}

bool HotplugDevice::ejectDevice()
{
	if (m_valid && umount() == 0) {
		m_dev = "";
		m_valid = false;
		m_space = 0;
		m_total = 0;
		m_free = 0;
		return true;
	}
	return false;
}

bool HotplugDevice::removeDevice(QString dev, bool isUpgrade)
{
	if (dev == m_dev) 
	{
		if (!isUpgrade)
		{
			umount();
		}
		else
		{
			umount(isUpgrade);
		}
		m_dev = "";
		m_valid = false;
		m_space = 0;
		m_total = 0;
		m_free = 0;
		return true;
	}

	qDebug() << QString("remove 1% failed!").arg(dev);
	return false;
}

void HotplugDevice::init()
{
	QFile file("/proc/mounts");
	if (file.open(QIODevice::ReadOnly)) 
	{
		QByteArray content = file.readAll();
		file.close();

		QTextStream out(&content);
		QMap<QString, QString> mountPoints;
		while (!out.atEnd()) 
		{
			QString line = out.readLine();
			QStringList list = line.split(' ');
			if (list.size() == 6) 
			{
				mountPoints.insert(list[1], list[0]);
			}
		}

		if (mountPoints.contains(m_node)) 
		{
			m_dev = mountPoints[m_node];
		}
	}


	if (m_dev.isEmpty()) 
	{
		QString tag = (m_medium == Type_USB) ? "usb" : "e0101";
		QDir dir("/dev/disk/by-path/");
		QFileInfoList infoList = dir.entryInfoList(QDir::NoDotAndDotDot);
		QString path;
		foreach(QFileInfo info, infoList) 
		{
			QString name = info.fileName();
			if (info.isSymLink() && name.contains("part")) 
			{
				if (name.contains(tag)) 
				{
					path = info.symLinkTarget();
					break;
				}
			}
		}
		if (!path.isEmpty()) 
		{
			int ret = mount(path, "vfat");
			if (ret == 22) 
			{
				ret = mount(path, "ntfs");
			}
			if (ret == 0) 
			{
				m_dev = path;
			}
			if (ret == -1)
			{
				m_remountPath = path;
				m_pTimer->start();
			}
		}
	}

	reset();
}

void HotplugDevice::reset()
{
#if __linux__
	QMutexLocker locker(&m_mutex);
	if (isMount() && QFileInfo::exists(m_dev)) {
		m_valid = true;
		struct statfs sfs;
		if (::statfs(m_node.toStdString().data(), &sfs) == 0) {
			qint64 totol = (qint64)sfs.f_blocks*(qint64)sfs.f_bsize / 1024 / 1024;
			qint64 free = (qint64)sfs.f_bavail*(qint64)sfs.f_bsize / 1024 / 1024;
			m_total = totol;
			m_free = free;

			if (m_total > 0) {
				m_space = (m_total - m_free) / m_total;
			}
			else {
				m_total = 0;
				m_free = 0;
				m_space = 0;
			}

		}
		else {
			m_total = 0;
			m_free = 0;
			m_space = 0;
		}
	}
	else {
		m_valid = false;
		m_total = 0;
		m_free = 0;
		m_space = 0;
	}
#endif
}

int HotplugDevice::mount(QString dev, QString format) 
{
    qDebug("zbx @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	QString mountPoint(m_node);
	if (!QFileInfo::exists(mountPoint)) {
		QDir dir;
		if (!dir.mkpath(mountPoint)) {
			qDebug() << "Failed to make  director.";
			return -1;
		}
	}

	QString strMount = QString("mount -t %1 -o umask=020 -o sync -o shortname=mixed -o utf8=yes %2 %3").
		arg(format).
		arg(dev).
		arg(mountPoint);
   // QProcess::execute(strMount);
    if (0 != QProcess::execute(strMount))
    {
        qDebug() << "@@@@@@zbc cmd failed";
        //emit sendSysCmdMsg(strMount);
    }
	
	if (isMount())
	{
#if __linux__
 		mountPoint.append("/mediatest");
        int fd = open(mountPoint.toLatin1(), O_RDWR | O_CREAT, 0777);

		if (fd < 0)
		{
			qDebug() << "Failed to make test director.";
			if (umount() == 0)
			{
				m_dev = "";
				m_valid = false;
				m_space = 0;
				m_total = 0;
				m_free = 0;
			}
			return -1;
		}
		else
		{
			close(fd);
			QFile::remove(mountPoint);
		}
		reset();
#endif
		return 0;
	}
	QDir dir;
	dir.rmpath(mountPoint);
	return  -1;
}

int HotplugDevice::umount(bool isUpgrade)
{
#if __linux__
	int ret = errno;
	QString rmpathCmd = QString("rm %1 -rf").arg(m_node);
	QString strMount = QString("umount %1").arg(m_node);
	if (!isUpgrade)
	{
		emit sendSysCmdMsg(strMount);
		if (isMount())
		{
			QString cmd = QString("umount -lf %1").arg(m_node);
			emit sendSysCmdMsg(cmd);
			if (!isMount())
			{
				ret = 0;
			}
		}
		else
		{
			ret = 0;
		}

		if (ret == 0)
		{
			QString mountPoint(m_node);
			if (QFileInfo::exists(mountPoint))
			{
				sendSysCmdMsg(rmpathCmd);
			}
		}
	}
	else
	{
		if (QProcess::execute(strMount) == 0)
		{
			qDebug() << "Umount success!";
			ret = 0;
		}
		else
		{
			qDebug() << "Umount again!";
			QString cmd = QString("umount -lf %1").arg(m_node);
			if (QProcess::execute(cmd) == 0)
			{
				ret = 0;
			}
		}

		if (ret == 0) 
		{
			QString mountPoint(m_node);
			if (QFileInfo::exists(mountPoint))
			{
				QProcess::execute(rmpathCmd);
			}
		}
		else if (ret == errno)
		{
			qDebug() << "Umount Error -" << errno << QString(strerror(errno)) << m_dev;
		}
	}
	return ret;
#else
	return 0;
#endif

}

bool HotplugDevice::isMount() const
{
#if __linux__
	QString path = m_node;
	if (QFileInfo::exists(path)) {
		struct stat mp, mpp;
		QString parentPath = path.append("/../");
		::stat(m_node.toStdString().data(), &mp);
		::stat(parentPath.toStdString().data(), &mpp);
		return mp.st_dev != mpp.st_dev;
	}
#endif
	return false;
}
