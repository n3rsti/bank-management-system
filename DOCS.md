# Documentation
## Table of contents
1. Storing data
   * [users data](#users_data)
   * [balance data](#balance_data)
   * [transactions data](#transactions_data)


### Storing data
All data is currently saved in txt files
<h4 id="users_data">Users data</h4>

Format:
```
    id: autoincrement positive integer
    login: string
    password: 256bit hash
    salt: 16 chars hash
```
* **id**: generated in **users.h/check_user_by_login** (last_user_id + 1)
* **login**: string containing any characters, 255 length
* **password**: hash generated using sha256 algorithm from password + random salt
* **salt**: randomly generated string, 16 length

<h4 id="balance_data">Balance data</h4>

Format:
```
    id: autoincrement positive integer
    balance: positive float number
```
* **id**: generated in **users.h/check_user_by_login** (last_user_id + 1)
* **balance**: when new user is created, balance value is set to 0
  * balance is stored in format with 6 decimal places because having 
  2 decimal places would require more calculations and updating balance would be slower

<h4 id="transactions_data">Transactions data</h4>

Format:
```
   payer_id: int
   payee_id: int
   amount: double
```