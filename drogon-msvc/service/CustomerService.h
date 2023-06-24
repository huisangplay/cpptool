//
// Created by ZHOU on 2023/6/11.
//

#ifndef MYDROGON_CUSTOMERSERVICE_H
#define MYDROGON_CUSTOMERSERVICE_H


#include<vector>
#include "../models/Customer.h"

class CustomerService {
    std::vector<drogon_model::sqlite3::Customer> getCustomerList();
};


#endif //MYDROGON_CUSTOMERSERVICE_H
