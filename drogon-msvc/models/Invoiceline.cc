/**
 *
 *  Invoiceline.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Invoiceline.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::sqlite3;

const std::string Invoiceline::Cols::_InvoiceLineId = "InvoiceLineId";
const std::string Invoiceline::Cols::_InvoiceId = "InvoiceId";
const std::string Invoiceline::Cols::_TrackId = "TrackId";
const std::string Invoiceline::Cols::_UnitPrice = "UnitPrice";
const std::string Invoiceline::Cols::_Quantity = "Quantity";
const std::string Invoiceline::primaryKeyName = "InvoiceLineId";
const bool Invoiceline::hasPrimaryKey = true;
const std::string Invoiceline::tableName = "invoiceline";

const std::vector<typename Invoiceline::MetaData> Invoiceline::metaData_={
{"InvoiceLineId","uint64_t","integer",8,1,1,1},
{"InvoiceId","uint64_t","integer",8,0,0,1},
{"TrackId","uint64_t","integer",8,0,0,1},
{"UnitPrice","std::string","numeric(10,2)",0,0,0,1},
{"Quantity","uint64_t","integer",8,0,0,1}
};
const std::string &Invoiceline::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Invoiceline::Invoiceline(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["InvoiceLineId"].isNull())
        {
            invoicelineid_=std::make_shared<uint64_t>(r["InvoiceLineId"].as<uint64_t>());
        }
        if(!r["InvoiceId"].isNull())
        {
            invoiceid_=std::make_shared<uint64_t>(r["InvoiceId"].as<uint64_t>());
        }
        if(!r["TrackId"].isNull())
        {
            trackid_=std::make_shared<uint64_t>(r["TrackId"].as<uint64_t>());
        }
        if(!r["UnitPrice"].isNull())
        {
            unitprice_=std::make_shared<std::string>(r["UnitPrice"].as<std::string>());
        }
        if(!r["Quantity"].isNull())
        {
            quantity_=std::make_shared<uint64_t>(r["Quantity"].as<uint64_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 5 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            invoicelineid_=std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            invoiceid_=std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            trackid_=std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            unitprice_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            quantity_=std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
    }

}

Invoiceline::Invoiceline(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            invoicelineid_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            invoiceid_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            trackid_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            unitprice_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            quantity_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[4]].asUInt64());
        }
    }
}

Invoiceline::Invoiceline(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("InvoiceLineId"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["InvoiceLineId"].isNull())
        {
            invoicelineid_=std::make_shared<uint64_t>((uint64_t)pJson["InvoiceLineId"].asUInt64());
        }
    }
    if(pJson.isMember("InvoiceId"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["InvoiceId"].isNull())
        {
            invoiceid_=std::make_shared<uint64_t>((uint64_t)pJson["InvoiceId"].asUInt64());
        }
    }
    if(pJson.isMember("TrackId"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["TrackId"].isNull())
        {
            trackid_=std::make_shared<uint64_t>((uint64_t)pJson["TrackId"].asUInt64());
        }
    }
    if(pJson.isMember("UnitPrice"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["UnitPrice"].isNull())
        {
            unitprice_=std::make_shared<std::string>(pJson["UnitPrice"].asString());
        }
    }
    if(pJson.isMember("Quantity"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["Quantity"].isNull())
        {
            quantity_=std::make_shared<uint64_t>((uint64_t)pJson["Quantity"].asUInt64());
        }
    }
}

void Invoiceline::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            invoicelineid_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[0]].asUInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            invoiceid_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[1]].asUInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            trackid_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            unitprice_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            quantity_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[4]].asUInt64());
        }
    }
}

void Invoiceline::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("InvoiceLineId"))
    {
        if(!pJson["InvoiceLineId"].isNull())
        {
            invoicelineid_=std::make_shared<uint64_t>((uint64_t)pJson["InvoiceLineId"].asUInt64());
        }
    }
    if(pJson.isMember("InvoiceId"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["InvoiceId"].isNull())
        {
            invoiceid_=std::make_shared<uint64_t>((uint64_t)pJson["InvoiceId"].asUInt64());
        }
    }
    if(pJson.isMember("TrackId"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["TrackId"].isNull())
        {
            trackid_=std::make_shared<uint64_t>((uint64_t)pJson["TrackId"].asUInt64());
        }
    }
    if(pJson.isMember("UnitPrice"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["UnitPrice"].isNull())
        {
            unitprice_=std::make_shared<std::string>(pJson["UnitPrice"].asString());
        }
    }
    if(pJson.isMember("Quantity"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["Quantity"].isNull())
        {
            quantity_=std::make_shared<uint64_t>((uint64_t)pJson["Quantity"].asUInt64());
        }
    }
}

const uint64_t &Invoiceline::getValueOfInvoicelineid() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if(invoicelineid_)
        return *invoicelineid_;
    return defaultValue;
}
const std::shared_ptr<uint64_t> &Invoiceline::getInvoicelineid() const noexcept
{
    return invoicelineid_;
}
void Invoiceline::setInvoicelineid(const uint64_t &pInvoicelineid) noexcept
{
    invoicelineid_ = std::make_shared<uint64_t>(pInvoicelineid);
    dirtyFlag_[0] = true;
}
const typename Invoiceline::PrimaryKeyType & Invoiceline::getPrimaryKey() const
{
    assert(invoicelineid_);
    return *invoicelineid_;
}

const uint64_t &Invoiceline::getValueOfInvoiceid() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if(invoiceid_)
        return *invoiceid_;
    return defaultValue;
}
const std::shared_ptr<uint64_t> &Invoiceline::getInvoiceid() const noexcept
{
    return invoiceid_;
}
void Invoiceline::setInvoiceid(const uint64_t &pInvoiceid) noexcept
{
    invoiceid_ = std::make_shared<uint64_t>(pInvoiceid);
    dirtyFlag_[1] = true;
}

const uint64_t &Invoiceline::getValueOfTrackid() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if(trackid_)
        return *trackid_;
    return defaultValue;
}
const std::shared_ptr<uint64_t> &Invoiceline::getTrackid() const noexcept
{
    return trackid_;
}
void Invoiceline::setTrackid(const uint64_t &pTrackid) noexcept
{
    trackid_ = std::make_shared<uint64_t>(pTrackid);
    dirtyFlag_[2] = true;
}

const std::string &Invoiceline::getValueOfUnitprice() const noexcept
{
    const static std::string defaultValue = std::string();
    if(unitprice_)
        return *unitprice_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Invoiceline::getUnitprice() const noexcept
{
    return unitprice_;
}
void Invoiceline::setUnitprice(const std::string &pUnitprice) noexcept
{
    unitprice_ = std::make_shared<std::string>(pUnitprice);
    dirtyFlag_[3] = true;
}
void Invoiceline::setUnitprice(std::string &&pUnitprice) noexcept
{
    unitprice_ = std::make_shared<std::string>(std::move(pUnitprice));
    dirtyFlag_[3] = true;
}

const uint64_t &Invoiceline::getValueOfQuantity() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if(quantity_)
        return *quantity_;
    return defaultValue;
}
const std::shared_ptr<uint64_t> &Invoiceline::getQuantity() const noexcept
{
    return quantity_;
}
void Invoiceline::setQuantity(const uint64_t &pQuantity) noexcept
{
    quantity_ = std::make_shared<uint64_t>(pQuantity);
    dirtyFlag_[4] = true;
}

void Invoiceline::updateId(const uint64_t id)
{
    invoicelineid_ = std::make_shared<uint64_t>(id);
}

const std::vector<std::string> &Invoiceline::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "InvoiceId",
        "TrackId",
        "UnitPrice",
        "Quantity"
    };
    return inCols;
}

void Invoiceline::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getInvoiceid())
        {
            binder << getValueOfInvoiceid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTrackid())
        {
            binder << getValueOfTrackid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getUnitprice())
        {
            binder << getValueOfUnitprice();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getQuantity())
        {
            binder << getValueOfQuantity();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Invoiceline::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    return ret;
}

void Invoiceline::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getInvoiceid())
        {
            binder << getValueOfInvoiceid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTrackid())
        {
            binder << getValueOfTrackid();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getUnitprice())
        {
            binder << getValueOfUnitprice();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getQuantity())
        {
            binder << getValueOfQuantity();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Invoiceline::toJson() const
{
    Json::Value ret;
    if(getInvoicelineid())
    {
        ret["InvoiceLineId"]=(Json::UInt64)getValueOfInvoicelineid();
    }
    else
    {
        ret["InvoiceLineId"]=Json::Value();
    }
    if(getInvoiceid())
    {
        ret["InvoiceId"]=(Json::UInt64)getValueOfInvoiceid();
    }
    else
    {
        ret["InvoiceId"]=Json::Value();
    }
    if(getTrackid())
    {
        ret["TrackId"]=(Json::UInt64)getValueOfTrackid();
    }
    else
    {
        ret["TrackId"]=Json::Value();
    }
    if(getUnitprice())
    {
        ret["UnitPrice"]=getValueOfUnitprice();
    }
    else
    {
        ret["UnitPrice"]=Json::Value();
    }
    if(getQuantity())
    {
        ret["Quantity"]=(Json::UInt64)getValueOfQuantity();
    }
    else
    {
        ret["Quantity"]=Json::Value();
    }
    return ret;
}

Json::Value Invoiceline::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 5)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getInvoicelineid())
            {
                ret[pMasqueradingVector[0]]=(Json::UInt64)getValueOfInvoicelineid();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getInvoiceid())
            {
                ret[pMasqueradingVector[1]]=(Json::UInt64)getValueOfInvoiceid();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getTrackid())
            {
                ret[pMasqueradingVector[2]]=(Json::UInt64)getValueOfTrackid();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getUnitprice())
            {
                ret[pMasqueradingVector[3]]=getValueOfUnitprice();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getQuantity())
            {
                ret[pMasqueradingVector[4]]=(Json::UInt64)getValueOfQuantity();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getInvoicelineid())
    {
        ret["InvoiceLineId"]=(Json::UInt64)getValueOfInvoicelineid();
    }
    else
    {
        ret["InvoiceLineId"]=Json::Value();
    }
    if(getInvoiceid())
    {
        ret["InvoiceId"]=(Json::UInt64)getValueOfInvoiceid();
    }
    else
    {
        ret["InvoiceId"]=Json::Value();
    }
    if(getTrackid())
    {
        ret["TrackId"]=(Json::UInt64)getValueOfTrackid();
    }
    else
    {
        ret["TrackId"]=Json::Value();
    }
    if(getUnitprice())
    {
        ret["UnitPrice"]=getValueOfUnitprice();
    }
    else
    {
        ret["UnitPrice"]=Json::Value();
    }
    if(getQuantity())
    {
        ret["Quantity"]=(Json::UInt64)getValueOfQuantity();
    }
    else
    {
        ret["Quantity"]=Json::Value();
    }
    return ret;
}

bool Invoiceline::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("InvoiceLineId"))
    {
        if(!validJsonOfField(0, "InvoiceLineId", pJson["InvoiceLineId"], err, true))
            return false;
    }
    if(pJson.isMember("InvoiceId"))
    {
        if(!validJsonOfField(1, "InvoiceId", pJson["InvoiceId"], err, true))
            return false;
    }
    else
    {
        err="The InvoiceId column cannot be null";
        return false;
    }
    if(pJson.isMember("TrackId"))
    {
        if(!validJsonOfField(2, "TrackId", pJson["TrackId"], err, true))
            return false;
    }
    else
    {
        err="The TrackId column cannot be null";
        return false;
    }
    if(pJson.isMember("UnitPrice"))
    {
        if(!validJsonOfField(3, "UnitPrice", pJson["UnitPrice"], err, true))
            return false;
    }
    else
    {
        err="The UnitPrice column cannot be null";
        return false;
    }
    if(pJson.isMember("Quantity"))
    {
        if(!validJsonOfField(4, "Quantity", pJson["Quantity"], err, true))
            return false;
    }
    else
    {
        err="The Quantity column cannot be null";
        return false;
    }
    return true;
}
bool Invoiceline::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                     const std::vector<std::string> &pMasqueradingVector,
                                                     std::string &err)
{
    if(pMasqueradingVector.size() != 5)
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
        else
        {
            err="The " + pMasqueradingVector[1] + " column cannot be null";
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
        else
        {
            err="The " + pMasqueradingVector[2] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[3] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[4].empty())
      {
          if(pJson.isMember(pMasqueradingVector[4]))
          {
              if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[4] + " column cannot be null";
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
bool Invoiceline::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("InvoiceLineId"))
    {
        if(!validJsonOfField(0, "InvoiceLineId", pJson["InvoiceLineId"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("InvoiceId"))
    {
        if(!validJsonOfField(1, "InvoiceId", pJson["InvoiceId"], err, false))
            return false;
    }
    if(pJson.isMember("TrackId"))
    {
        if(!validJsonOfField(2, "TrackId", pJson["TrackId"], err, false))
            return false;
    }
    if(pJson.isMember("UnitPrice"))
    {
        if(!validJsonOfField(3, "UnitPrice", pJson["UnitPrice"], err, false))
            return false;
    }
    if(pJson.isMember("Quantity"))
    {
        if(!validJsonOfField(4, "Quantity", pJson["Quantity"], err, false))
            return false;
    }
    return true;
}
bool Invoiceline::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                   const std::vector<std::string> &pMasqueradingVector,
                                                   std::string &err)
{
    if(pMasqueradingVector.size() != 5)
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
    else
    {
        err = "The value of primary key must be set in the json object for update";
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
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
      if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
      {
          if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
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
bool Invoiceline::validJsonOfField(size_t index,
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
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            if(!pJson.isUInt64())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isUInt64())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isUInt64())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 3:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 4:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
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