#ifndef _HISTORY_TRANSACTION_CPP_
#define _HISTORY_TRANSACTION_CPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// TEST DATA ON DIFFERENT DATA SETS
// Getting ACB To work on unsorted

// FOR SORT TRY IN ORDER
// Not in order
// Ascending
// Descending
// no values
// one value


// Constructor
// TASK 1
//

Transaction::Transaction( std::string ticker_symbol,
                         unsigned int day_date,
                         unsigned int month_date,
                         unsigned year_date,
                         bool buy_sell_trans,
                         unsigned int number_shares,
                         double trans_amount ):

    // NORMAL THINGS TO ASSIGN
    symbol{ticker_symbol},
    day{day_date},
    month{month_date},
    year{year_date},

    // MUST BE UPDATED TO STRINGS AS BELOW
    trans_type{},

    // NORMAL THINGS TO ASSIGN
    shares{number_shares},
    amount{trans_amount},

    // ASSIGNED THE GLOBALLY ASSIGNED TRANS ID
    trans_id{assigned_trans_id},

    // THESE WILL BE CHANGED LATER BUT ARE FIRST INITIALIZED TO NORMAL VALS
    acb{},
    acb_per_share{},
    share_balance{},
    cgl{},
    p_next{}

    {
        if (buy_sell_trans)
        {
            trans_type = "Buy";
        }
        else
        {
            trans_type = "Sell";
        }

        assigned_trans_id++;
    }

// Destructor
// TASK 1
//

Transaction::~Transaction()
{
    p_next = nullptr;
}

// Overloaded < operator.
// TASK 2
//

bool Transaction::operator<( Transaction const &other )
{
    if (this->get_year() < other.get_year())
    {
        return true;
    }
    else if (this->get_year() > other.get_year())
    {
        return false;
    }
    else
    {
        if (this->get_month() < other.get_month())
        {
            return true;
        }
        else if (this->get_month() > other.get_month())
        {
            return false;
        }
        else
        {
            if (this->get_day() < other.get_day())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    // FIRST CHECK THE DATES, WHICH COMES FIRST
    // IE, TRUE IF THE INSTANCE COMES BEFORE THE PARAMETER

    // IF BOTH HAVE THE SAME DATE, CHECK THE TRANS_ID:
    // TRUE IF TRANS_ID OF INSTANCE IS SMALLER THAN THE PARAMETER
}



// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}



////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//
History::History():
    p_head{nullptr}
{

}

// Destructor
// TASK 3
//
History::~History()
{
    Transaction *p_temp{nullptr};

    // Keep creating *p_temp at *p_head and delete p_head

    while (get_p_head() != nullptr) // Loop will stop once p_head points to the nullptr and is not representing a transaction
    {
        p_temp = get_p_head();
        p_head = get_p_head()->get_next();
        delete p_temp;
        p_temp = nullptr;
    }

    p_head = nullptr;
    p_temp = nullptr;
}

// read_transaction(...): Read the transaction history from file.
// TASK 4
//

void History::read_history()
{
    ece150::open_file();
//    std::cout << "File Opened" << std::endl;

    while(ece150::next_trans_entry())
    {
        std::string new_symbol{ece150::get_trans_symbol()};
        unsigned int new_day{ece150::get_trans_day()};
        unsigned int new_month{ece150::get_trans_month()};
        unsigned new_year{ece150::get_trans_year()};
        bool bs_trans{ece150::get_trans_type()};
        unsigned int new_share_number{ece150::get_trans_shares()};
        double new_trans_amount{ece150::get_trans_amount()};

//        std::cout << "Found new entry:" << std::endl;
//        std::cout << "SYMBOL:\t" << new_symbol << std::endl;
//        std::cout << "DAY:\t" << new_day << std::endl;
//        std::cout << "MONTH:\t" << new_month << std::endl;
//        std::cout << "YEAR:\t" << new_year << std::endl;
//        std::cout << "BUY?\t" << bs_trans << std::endl;
//        std::cout << "SHARE NUMBER:\t" << new_share_number << std::endl;
//        std::cout << "TRANS AMOUNT:\t" << new_trans_amount << std::endl;


        Transaction *new_transaction{new Transaction{new_symbol, new_day, new_month, new_year, bs_trans, new_share_number, new_trans_amount}};

//        std::cout << "New Transaction Created" << std::endl;

        insert(new_transaction);
        new_transaction = nullptr;
    }



    ece150::close_file();
//    std::cout << "Closing File" << std::endl;
}


// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans)
{
        p_new_trans->set_next(nullptr);
        Transaction *node_trans{get_p_head()};

        if (node_trans != nullptr)
        {
            while(node_trans->get_next() != nullptr)
            {
                node_trans = node_trans->get_next();
            }
            node_trans->set_next(p_new_trans);
        }
        else
        {
            p_head = p_new_trans;
        }

        node_trans = nullptr;
        p_new_trans = nullptr;
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date()
{
    Transaction *p_node{ get_p_head()};

    if (p_node == nullptr || p_node->get_next() == nullptr)
    {
        return;
    }

//    std::cout << ll_size << std::endl;

    Transaction *p_sorted{};

    Transaction *smallest_trans{get_p_head()};


    while (get_p_head() != nullptr)
    {
        // Finding the smallest node in the History list
        p_node = get_p_head();
        smallest_trans = get_p_head();
        while (p_node != nullptr) {

            if (*(smallest_trans) < *(p_node))
            {
                // Do Nothing
            }
            else if (*(p_node) < *(smallest_trans))
            {
                smallest_trans = p_node;
            }
            else if (smallest_trans->get_trans_id() < p_node->get_trans_id())
            {
                // Do Nothing
            }
            else
            {
                smallest_trans = p_node;
            }
            p_node = p_node->get_next();
        }
            // Removing from original list
            p_node = get_p_head();
            if (smallest_trans == get_p_head())
            {
                p_head = smallest_trans->get_next();
            }
            else
            {
                while (p_node->get_next() != nullptr) {
                    if (p_node->get_next() == smallest_trans)
                    {
                        p_node->set_next(smallest_trans->get_next());
                        break;
                    }
                    p_node = p_node->get_next();
                }
            }


            smallest_trans->set_next(nullptr);

        // Adding to sorted list

        Transaction *p_sorted_node = p_sorted;
        if (p_sorted_node != nullptr)
        {
            // Adding to sorted list
            while(p_sorted_node->get_next() != nullptr)
            {
                p_sorted_node = p_sorted_node->get_next();
            }
            p_sorted_node->set_next(smallest_trans);
        }
        else
        {
            p_sorted = smallest_trans;
        }
        p_sorted_node = nullptr;

    }
    p_head = p_sorted;


    p_node = nullptr;
    p_sorted = nullptr;
    smallest_trans = nullptr;

    return;
}


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//

// If a Transaction is a Buy, get_trans_type() will return True
void History::update_acb_cgl()
{
    sort_by_date();
    Transaction *p_node{get_p_head()};

    double new_acb{};
    double new_acb_per_share{};
    unsigned int new_share_balance{};
    double new_cgl{};

    while ( p_node != nullptr ) {

        // Calculating Share Balance
        if (p_node->get_trans_type()) // Buy
        {
            new_share_balance += p_node->get_shares();
        }
        else
        {
            new_share_balance -= p_node->get_shares();
        }
        p_node->set_share_balance(new_share_balance);


        // Calculating ACB
        if (p_node->get_trans_type()) // Buy
        {
            new_acb += p_node->get_amount();
        }
        else
        {
            new_acb -= p_node->get_shares()*new_acb_per_share;
        }
        p_node->set_acb(new_acb);



        // Calculating ACB/Share
        if (p_node->get_trans_type()) // Buy
        {
            if (p_node->get_share_balance() != 0)
            {
                new_acb_per_share = p_node->get_acb() / p_node->get_share_balance();
            }
            else
            {
                new_acb_per_share = 0;
            }
        }
        p_node->set_acb_per_share(new_acb_per_share);


        // Calculating CGL
        if (!(p_node->get_trans_type()))
        {
           new_cgl = (p_node->get_amount()-(p_node->get_shares()*p_node->get_acb_per_share()));
           p_node->set_cgl(new_cgl);
        }



        p_node = p_node->get_next(); // Traversing the List
    }

    p_node = nullptr;
    return;
}



// compute_cgl(): Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year)
{
    update_acb_cgl();
    Transaction *p_node{get_p_head()};
    double total_cgl{};

    while ( p_node != nullptr ) {

        if (p_node->get_year() == year && !(p_node->get_trans_type()))
        {
            total_cgl += p_node->get_cgl();
        }
        p_node = p_node->get_next();
    }

    p_node = nullptr;

    return total_cgl;
}



// print() Print the transaction history.
//TASK 9
//
// Print the transaction history.
//
void History::print()
{
    std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
    Transaction *node_transaction{get_p_head()};
    while (node_transaction != nullptr)
    {
        node_transaction->print();
        node_transaction = node_transaction->get_next();
    }
    std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;

    node_transaction = nullptr;
}




// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }


#endif
