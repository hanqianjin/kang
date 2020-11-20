#pragma once
#include <string>
#include "ajson/ajson.hpp"

namespace model
{
	class BaseData
	{
	public:
		BaseData() = default;
		~BaseData() = default;

        virtual bool	toJson(std::string &json) { return false; }
        virtual bool    fromJson(const std::string &json) { return false; }

	protected:
		template<typename structType>
		bool encode(std::string &json, const structType &object, std::string &errMsg)//to json
		{
			bool bRet = true;
			ajson::string_stream ss;
			ajson::save_to(ss, object);

			json = ss.str();
			return bRet;
		}

		template<typename structType>
		bool decode(const std::string &json, structType &object, std::string &errMsg) //from json
		{
			bool bRet = true;
			try
			{
				ajson::load_from_buff(object, const_cast<char*>(json.c_str()));
			}
			catch (const ajson::exception &ex)
			{
				errMsg = ex.what();
				bRet = false;
			}
			catch (const std::exception &ex)
			{
				errMsg = ex.what();
				bRet = false;
			}
			return bRet;
		}
	};
}
