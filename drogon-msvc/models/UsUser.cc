/**
 *
 *  UsUser.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "UsUser.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::sqlite3;

const std::string UsUser::Cols::_user_name = "user_name";
const std::string UsUser::Cols::_user_password = "user_password";
const std::string UsUser::Cols::_user_id = "user_id";
const std::string UsUser::primaryKeyName = "user_id";
const bool UsUser::hasPrimaryKey = true;
const std::string UsUser::tableName = "us_user";

const std::vector<typename UsUser::MetaData> UsUser::metaData_={
{"user_name","std::string","text",0,0,0,0},
{"user_password","std::string","",0,0,0,0},
{"user_id","uint64_t","integer",8,1,1,0}
};
const std::string &UsUser::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
UsUser::UsUser(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["user_name"].isNull())
        {
            userName_=std::make_shared<std::string>(r["user_name"].as<std::string>());
        }
        if(!r["user_password"].isNull())
        {
            userPassword_=std::make_shared<std::string>(r["user_password"].as<std::string>());
        }
        if(!r["user_id"].isNull())
        {
            userId_=std::make_shared<uint64_t>(r["user_id"].as<uint64_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 3 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            userName_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            userPassword_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            userId_=std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
    }

}

UsUser::UsUser(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            userName_=std::make_shared<std::string>(pJson[pMasqueradingVector[0]].asString());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            userPassword_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            userId_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
}

UsUser::UsUser(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("user_name"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["user_name"].isNull())
        {
            userName_=std::make_shared<std::string>(pJson["user_name"].asString());
        }
    }
    if(pJson.isMember("user_password"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["user_password"].isNull())
        {
            userPassword_=std::make_shared<std::string>(pJson["user_password"].asString());
        }
    }
    if(pJson.isMember("user_id"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["user_id"].isNull())
        {
            userId_=std::make_shared<uint64_t>((uint64_t)pJson["user_id"].asUInt64());
        }
    }
}

void UsUser::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            userName_=std::make_shared<std::string>(pJson[pMasqueradingVector[0]].asString());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            userPassword_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            userId_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
}

void UsUser::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("user_name"))
    {
        dirtyFlag_[0] = true;
        if(!pJson["user_name"].isNull())
        {
            userName_=std::make_shared<std::string>(pJson["user_name"].asString());
        }
    }
    if(pJson.isMember("user_password"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["user_password"].isNull())
        {
            userPassword_=std::make_shared<std::string>(pJson["user_password"].asString());
        }
    }
    if(pJson.isMember("user_id"))
    {
        if(!pJson["user_id"].isNull())
        {
            userId_=std::make_shared<uint64_t>((uint64_t)pJson["user_id"].asUInt64());
        }
    }
}

const std::string &UsUser::getValueOfUserName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(userName_)
        return *userName_;
    return defaultValue;
}
const std::shared_ptr<std::string> &UsUser::getUserName() const noexcept
{
    return userName_;
}
void UsUser::setUserName(const std::string &pUserName) noexcept
{
    userName_ = std::make_shared<std::string>(pUserName);
    dirtyFlag_[0] = true;
}
void UsUser::setUserName(std::string &&pUserName) noexcept
{
    userName_ = std::make_shared<std::string>(std::move(pUserName));
    dirtyFlag_[0] = true;
}
void UsUser::setUserNameToNull() noexcept
{
    userName_.reset();
    dirtyFlag_[0] = true;
}

const std::string &UsUser::getValueOfUserPassword() const noexcept
{
    const static std::string defaultValue = std::string();
    if(userPassword_)
        return *userPassword_;
    return defaultValue;
}
const std::shared_ptr<std::string> &UsUser::getUserPassword() const noexcept
{
    return userPassword_;
}
void UsUser::setUserPassword(const std::string &pUserPassword) noexcept
{
    userPassword_ = std::make_shared<std::string>(pUserPassword);
    dirtyFlag_[1] = true;
}
void UsUser::setUserPassword(std::string &&pUserPassword) noexcept
{
    userPassword_ = std::make_shared<std::string>(std::move(pUserPassword));
    dirtyFlag_[1] = true;
}
void UsUser::setUserPasswordToNull() noexcept
{
    userPassword_.reset();
    dirtyFlag_[1] = true;
}

const uint64_t &UsUser::getValueOfUserId() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if(userId_)
        return *userId_;
    return defaultValue;
}
const std::shared_ptr<uint64_t> &UsUser::getUserId() const noexcept
{
    return userId_;
}
void UsUser::setUserId(const uint64_t &pUserId) noexcept
{
    userId_ = std::make_shared<uint64_t>(pUserId);
    dirtyFlag_[2] = true;
}
void UsUser::setUserIdToNull() noexcept
{
    userId_.reset();
    dirtyFlag_[2] = true;
}
const typename UsUser::PrimaryKeyType & UsUser::getPrimaryKey() const
{
    assert(userId_);
    return *userId_;
}

void UsUser::updateId(const uint64_t id)
{
    userId_ = std::make_shared<uint64_t>(id);
}

const std::vector<std::string> &UsUser::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "user_name",
        "user_password",
    };
    return inCols;
}

void UsUser::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getUserName())
        {
            binder << getValueOfUserName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getUserPassword())
        {
            binder << getValueOfUserPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> UsUser::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    return ret;
}

void UsUser::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getUserName())
        {
            binder << getValueOfUserName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getUserPassword())
        {
            binder << getValueOfUserPassword();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value UsUser::toJson() const
{
    Json::Value ret;
    if(getUserName())
    {
        ret["user_name"]=getValueOfUserName();
    }
    else
    {
        ret["user_name"]=Json::Value();
    }
    if(getUserPassword())
    {
        ret["user_password"]=getValueOfUserPassword();
    }
    else
    {
        ret["user_password"]=Json::Value();
    }
    if(getUserId())
    {
        ret["user_id"]=(Json::UInt64)getValueOfUserId();
    }
    else
    {
        ret["user_id"]=Json::Value();
    }
    return ret;
}

Json::Value UsUser::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 3)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getUserName())
            {
                ret[pMasqueradingVector[0]]=getValueOfUserName();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getUserPassword())
            {
                ret[pMasqueradingVector[1]]=getValueOfUserPassword();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getUserId())
            {
                ret[pMasqueradingVector[2]]=(Json::UInt64)getValueOfUserId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getUserName())
    {
        ret["user_name"]=getValueOfUserName();
    }
    else
    {
        ret["user_name"]=Json::Value();
    }
    if(getUserPassword())
    {
        ret["user_password"]=getValueOfUserPassword();
    }
    else
    {
        ret["user_password"]=Json::Value();
    }
    if(getUserId())
    {
        ret["user_id"]=(Json::UInt64)getValueOfUserId();
    }
    else
    {
        ret["user_id"]=Json::Value();
    }
    return ret;
}

bool UsUser::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("user_name"))
    {
        if(!validJsonOfField(0, "user_name", pJson["user_name"], err, true))
            return false;
    }
    if(pJson.isMember("user_password"))
    {
        if(!validJsonOfField(1, "user_password", pJson["user_password"], err, true))
            return false;
    }
    if(pJson.isMember("user_id"))
    {
        if(!validJsonOfField(2, "user_id", pJson["user_id"], err, true))
            return false;
    }
    return true;
}
bool UsUser::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                std::string &err)
{
    if(pMasqueradingVector.size() != 3)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool UsUser::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("user_name"))
    {
        if(!validJsonOfField(0, "user_name", pJson["user_name"], err, false))
            return false;
    }
    if(pJson.isMember("user_password"))
    {
        if(!validJsonOfField(1, "user_password", pJson["user_password"], err, false))
            return false;
    }
    if(pJson.isMember("user_id"))
    {
        if(!validJsonOfField(2, "user_id", pJson["user_id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    return true;
}
bool UsUser::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                              const std::vector<std::string> &pMasqueradingVector,
                                              std::string &err)
{
    if(pMasqueradingVector.size() != 3)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool UsUser::validJsonOfField(size_t index,
                              const std::string &fieldName,
                              const Json::Value &pJson,
                              std::string &err,
                              bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isUInt64())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}