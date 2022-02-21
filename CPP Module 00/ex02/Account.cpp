#include "Account.hpp"
#include <ctime>
#include <string>
#include <iostream>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

void Account::_displayTimestamp( void )
{
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);
    std::cout << "[" << t->tm_year + 1900;
    if (t->tm_mon + 1 < 10)
        std::cout << "0"; 
    std::cout << t->tm_mon + 1 << t->tm_mday << "_" 
    << t->tm_hour << t->tm_min << t->tm_sec << "]";
}

int	Account::getNbAccounts( void )
{
    return (Account::_nbAccounts);
}

int Account::getTotalAmount( void )
{
    return (Account::_totalAmount);
}
int Account::getNbDeposits( void )
{
    return (Account::_totalNbDeposits);
}

int Account::getNbWithdrawals( void )
{
    return (Account::_totalNbWithdrawals);
}

Account::~Account()
{
    Account::_nbAccounts -= 1;
    Account::_totalAmount -= _amount;
    Account::_totalNbDeposits -= _nbDeposits;
    Account::_totalNbWithdrawals -= _nbWithdrawals;

    _displayTimestamp();
    std::cout << " "
    << "index:" << _accountIndex << ";"
    << "amount:" << _amount
    << ";closed" << std::endl;
}

Account::Account( int initial_deposit )
{
    _accountIndex = getNbAccounts();
    Account::_nbAccounts += 1; 
	_amount = initial_deposit;
    Account::_totalAmount += initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;

    _displayTimestamp();
    std::cout << " "
    << "index:" << _accountIndex << ";"
    << "amount:" << _amount << ";created" << std::endl;
}

void Account::displayAccountsInfos( void )
{
    _displayTimestamp();
    std::cout << " "
    << "accounts:" << getNbAccounts() << ";"
	<< "total:" << getTotalAmount() << ";"
	<< "deposits:" << getNbDeposits() << ";"
	<< "withdrawals:" << getNbWithdrawals()
    << std::endl;
}

int	Account::checkAmount( void ) const
{
    return (_amount);
}

void Account::displayStatus(void) const
{
    _displayTimestamp();
    
    std::cout << " " 
    << "index:" << _accountIndex << ";"
    << "amount:" << _amount << ";"
    << "deposits:" << _nbDeposits << ";"
    << "withdrawals:" << _nbWithdrawals << std::endl;
}

void	Account::makeDeposit( int deposit )
{
    int previous = _amount;
    _amount += deposit;
    _nbDeposits += 1;
    Account::_totalNbDeposits += 1;
    Account::_totalAmount += deposit;

    _displayTimestamp();
    std::cout << " "
    << "index:" << _accountIndex << ";"
    << "p_amount:" << previous << ";"
    << "deposit:" << deposit << ";"
    << "amount:" << _amount << ";"
    << "nb_deposits:" << _nbDeposits << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal )
{
    int previous = _amount;
       
    _displayTimestamp();
    std::cout << " "
    << "index:" << _accountIndex << ";"
    << "p_amount:" << previous << ";";
    if (withdrawal > _amount)
    {
        std::cout << "withdrawal:refused" << std::endl;
        return (false);
    }
    else
    {
        _amount -= withdrawal;
        Account::_totalAmount -= withdrawal;
        _nbWithdrawals += 1;
        Account::_totalNbWithdrawals += 1;

        std::cout
        << "withdrawal:" << withdrawal << ";"
        << "amount:" << _amount << ";"
        << "nb_withdrawals:" << _nbWithdrawals << std::endl;
        return (true);
    }
}