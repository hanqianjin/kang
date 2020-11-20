#ifndef HotplugWatcher_H_
#define HotplugWatcher_H_

#include <QObject>
#include <QDebug>
#include <QSocketNotifier>
#include <QMutex>
#include <QTimer>

/*扩展存储媒介*/
typedef enum Media_Type {
	Type_USB,         //USB
	Type_SD,          //SD卡
	Type_Unknow,      //不能识别
}Media_Type;

#ifdef __linux__
#define SD_PATH       "/tmp/SD/"                //sd卡挂载路径
#define USB_PATH_1      "/tmp/USB/"               //U盘挂载路径
#else
#define SD_PATH       "./root/SD/"                //sd卡挂载路径
#define USB_PATH_1      "./root/USB/"               //U盘挂载路径
#endif

class HotplugDevice : public QObject
{
	Q_OBJECT
public:
	HotplugDevice(Media_Type type, QObject* parent = 0);

	bool isExist();
	bool isExistDev();
	bool addDevice(QString dev);
	bool removeDevice(QString dev, bool isUpgrade = false);
	bool ejectDevice();
	qreal getPercent() { return m_space; }
	qreal getTotalSize() { return m_total; }
	qreal getFreeSize() { return m_free; }
	QString getDevice() { return m_dev; }

	int mount(QString dev, QString format);
	int umount(bool isUpgrade = false);
	void reset();

signals:
	void sigFormatUnrecognized();
	void sendSysCmdMsg(const QString &Cmd);
	void mediaConnectedFail();
private slots:
	void onTimerOut();

private:
	void init();

	bool isMount() const;

private:
	QMutex m_mutex;
	const Media_Type m_medium;

	bool m_valid;
	qreal m_space;
	qreal m_total;
	qreal m_free;
	QString m_dev;
	QString m_node;
	QTimer  *m_pTimer;
	QString m_remountPath;
};

class HotplugWatcher : public QObject
{
	Q_OBJECT
public:
	explicit HotplugWatcher(QObject *parent = 0);

signals:
	void sigUsbDeviceAdded();
	void sigMmcDeviceAdded();
	void sigUsbDeviceChanged();
	void sigMmcDeviceChanged();
	void sigUsbDeviceRemoved();
	void sigMmcDeviceRemoved();
	void sigUsbStorageUpdated(QString action, QString dev);
	void sigMmcStorageUpdated(QString action, QString dev);
	void sigtmcUsbDeviceRemoved();
	void sigtmcUsbDeviceAdded();
	private slots:
	void slotReadyRead();

private:
	int initialize();
	/**
	* @brief: 删除挂载点路径
	* @return: void
	*/
	void removeMountPath();

private:
	QSocketNotifier* m_notifier;
};
#endif
