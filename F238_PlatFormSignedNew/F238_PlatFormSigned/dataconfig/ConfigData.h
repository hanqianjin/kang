#pragma once
#include "BaseData.h"

#include "Platform_def.h"
#include "SA_def.h"

namespace model
{
	class ConfigData : public BaseData
	{
	public:
		ConfigData() = default;
		virtual ~ConfigData() = default;
		
        virtual void update(const std::vector<char> &buffer) {}
        virtual std::vector<char> data() { return std::vector<char>(); }
	};

	class SAConfigData : public ConfigData
	{
	public:
		virtual bool	toJson(std::string &json) override 
        { std::string errMsg;
            bool ret = encode(json, m_data, errMsg);
            if (!ret)
            {
                //BOOST_LOG(test_lg::get()) << "platform cfg data to json failed: " << errMsg;
            }
            return ret;
        }
		virtual bool    fromJson(const std::string &json) override 
        {
            std::string errMsg;
            bool ret = decode(json, m_data, errMsg);
            if (!ret)
            {
                //BOOST_LOG(test_lg::get()) << "platform cfg data from json failed: " << errMsg;
            }
            return ret;
        }
        SAAllConfig m_data;
	};

	class RTSAConfigData : public ConfigData
	{
	public:
		virtual bool	toJson(std::string &json) override
		{
			return false;
        }
		virtual bool    fromJson(const std::string &json) override
		{
			return false;
        }
	};

	class LTEFDDConfigData : public ConfigData
	{
	public:
		virtual bool	toJson(std::string &json) override
		{
			return false;
        }
		virtual bool    fromJson(const std::string &json) override
		{
			return false;
        }
	};

	class LTETDDConfigData : public ConfigData
	{
	public:
		virtual bool	toJson(std::string &json) override
		{
			return false;
        }
		virtual bool    fromJson(const std::string &json) override
		{
			return false;
        }
	};

	class N5GConfigData : public ConfigData
	{
	public:
		virtual bool	toJson(std::string &json) override
		{
			return false;
        }
		virtual bool    fromJson(const std::string &json) override
		{
			return false;
        }
	};

	class PlatformConfigData : public ConfigData
	{
	public:
		virtual bool	toJson(std::string &json) override
		{
			std::string errMsg;
			bool ret = encode(json, m_data, errMsg);
			if (!ret)
			{
                //BOOST_LOG(test_lg::get()) << "platform cfg data to json failed: " << errMsg;
			}
			return ret;
        }

		virtual bool    fromJson(const std::string &json) override
		{
			std::string errMsg;
			bool ret = decode(json, m_data, errMsg);
			if (!ret)
			{
                //BOOST_LOG(test_lg::get()) << "platform cfg data from json failed: " << errMsg;
			}
			return ret;
        }

        Plt_State_Param_def	m_data;
	};

    class NotifyConfigData : public ConfigData
    {
    public:
        virtual bool	toJson(std::string &json) override
        {
            std::string errMsg;
            bool ret = encode(json, m_data, errMsg);
            if (!ret)
            {
                //BOOST_LOG(test_lg::get()) << "platform cfg data to json failed: " << errMsg;
            }
            return ret;
        }

        virtual bool    fromJson(const std::string &json) override
        {
            std::string errMsg;
            bool ret = decode(json, m_data, errMsg);
            if (!ret)
            {
                //BOOST_LOG(test_lg::get()) << "platform cfg data from json failed: " << errMsg;
            }
            return ret;
        }

        ModChange_Notice_Msg	m_data;
    };
}
