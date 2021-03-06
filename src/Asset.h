// Author: YWiyogo
// Descr.: The asset description

#ifndef Asset_H
#define Asset_H

#include "MsgQueue.h"
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
using namespace std;

struct YearlyReturn
{
  int _year;
  float _total_value;
  float _total_return;
  // return in percent
  float _return_in_percent;
  YearlyReturn(int year, float val, float ret, float ret_percent)
      : _year(year), _total_value(val), _total_return(ret),
        _return_in_percent(ret_percent){};
};

class Asset : public std::enable_shared_from_this<Asset>
{
public:
  enum class Type
  {
    Stock,
    ETF,
    Bond,
    Real_Estate,
    Crypto,
    Commodity,
    Others
  };
  static const map<string, Type> _typeMap;
  // constructor & destructor
  Asset(string id, string name, Type type);
  ~Asset();

  void registerTransaction(time_t reg_date, float amount, float price_incl_fees);

  void updateYearlyReturn(time_t reg_date, float total_value,
                          float returns = 0.);

  // get the asset id
  string getId() const;
  // get the asset name
  string getName() const;
  // Get the asset's amount
  float getAmount() const;
  float getSpending() const;
  float getAvgPrice() const;
  float getCurrPrice() const;
  float getCurrValue() const;
  float getDiff() const;
  float getDiffInPercent() const;
  float getReturn() const;
  float getReturnInPercent() const;
  float getProfitLoss() const;
  // Get the asset type
  Type getType() const;

  void setCurrPrice(float price);

  void updateYearlyRoi(time_t reg_date, float value);
  // get the realized RoI
  const map<time_t, float> &getRois();

protected:
  std::shared_ptr<Asset> get_shared_this() { return shared_from_this(); }

  /* data */
  string _id;
  string _name;
  // asset type
  Type _type;
  // total amount of the asset
  float _amount;
  // total spending
  float _spending;
  // average buying price
  float _avg_price;
  // current price
  float _curr_price;
  // current total value
  float _curr_value;

  // Difference to avg buying price
  float _diff;
  // Difference to avg buying price in percent
  float _diff_in_percent;

  // asset return in percent
  float _return;
  float _return_in_percent;

  float _profit_loss;
  float _profit_in_percent;
  float _last_accumulated;
  // list of the returns with its value and its returns
  map<int, YearlyReturn> _return_years;
  // date time, roi value not accumulated
  map<time_t, float> _rois;
  static mutex _mtx;
};

#endif