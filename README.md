# Gas-station-manager
Developed a system in C programming language to manage operations for a gas company

Introduction:<br>
The system is a dynamic solution designed for managing a network of fuel stations. It addresses all necessary aspects of network management, from processing data from text or binary files to adding data across various domains managed by the company. The system handles data from multiple domains, including active stations, suppliers, employees, customers, fueling pumps, vehicle fleets, and delivery lists. It utilizes special tools such as sorting, binary search, data compression, and more.

The system can display data on the screen or export it to any file type (text or binary) and also allows individual data output for specific areas upon request. It is always available for adding data in any domain managed by the company in an accessible and efficient manner, providing specific error messages if the user inputs incorrect data due to the unique structure of most of the data formats.

Structure Descriptions:

Car:
A structure that describes a car with the following data: unique vehicle number, vehicle type, and fuel type used.

Pump:
A structure that describes a fuel pump with the following data: fuel type and unique pump code.

Person:
A structure that describes a person with the following data: name, unique ID number, and date of birth.

Person Manager:
A structure that describes the management of a group of persons (Person) and the number of persons in the group.

Customer:
A structure that describes a customer with the following data: name, unique ID number, date of birth (Person), the vehicle they drive, and their expenses.

Employee:
A structure that describes an employee in the network with the following data: name, unique ID number, date of birth (Person), and salary.

Date:
A structure that describes a date with the following data: day, month, and year.

Refinery:
A structure that describes a fuel supplier with the following data: unique supplier name, type of fuel supplied, and fuel cost.

Delivery:
A structure that describes a delivery with the following data: destination station, source supplier, delivery date, and the vehicle performing the delivery.

Station:
A structure that describes a fuel station with the following data: unique station name, city location, number of fuel pumps and their details, number of employees and their details, and number of customers and their details (this structure allows sorting and binary search on employees).

Station Manager:
A structure that describes the management of fuel stations using an array of stations, the number of stations in the array, and an array for managing people (Person Manager).

Company:
A structure that describes a fuel station company (network of fuel stations) with the following data: network name, an array for managing existing stations, a list of deliveries sorted by date, an array of suppliers and the number of suppliers, an array of the company's vehicle fleets, and the number of vehicles.

General System Structures:

Node:
A structure that describes a node in a list with the following data: any type of object and a pointer to the next node.

List:
A structure that describes a list holding data of type Node.

Data Compression Explanation for the Date Structure in a Binary File:
We used data compression on the Date structure for writing Date to a binary file as follows:
The Date structure holds three variables of type int (4 bytes each), totaling 12 bytes. By using bit packing, we managed to compress it to 3 bytes.

Compression method:

For the day (31 possibilities): 5 bits.
For the month (12 possibilities): 4 bits.
For the year (2048 possibilities, limited): 11 bits.
Total: 20 bits, or 3 bytes, are sufficient to store all Date data without loss.
Example compression:
Date 6/8/1995:

Day = 00110
Month = 1000
Year = 11111001011
Store in an array where each cell is a Byte, filling from MSB to LSB. It looks like this:
0 1 1 0 0 0 0 0 1 1 1 0 1 0 0 1 1 1 1 1 0 0 0 0

This method saves 9 bytes. Reading will be similar: read the array from left to right, the year = first 15 bits (4 MSB bits padded with 0), the month = 4 bits from bit 16 to 19, the day = 5 bits from bit 17 to 20.

User Operations:

The user can initialize the company via a text or binary file. Afterwards, the user can:

Print all company data at once to the screen.

Print individual company information, such as:

All active stations.
All supplier data.
Company's delivery list sorted by date.
Company's vehicle fleets.
Add data to the company, such as:

Adding a station with a unique name, city location, necessary pumps, customers, and employees.
Adding a pump to a specific station from the list of all company stations.
Adding a supplier with a unique name, fuel type, and cost.
Adding a delivery with the delivery date, source supplier, destination station, and vehicle.
Adding a vehicle to the company fleet with a unique number (10 digits), type, and fuel used.
Adding a customer to a specific station from the list by entering their details as a person (name, unique ID, date of birth) and expenses (randomly between 1-100).
Adding an employee to a specific station by entering their details as a person and their salary.
Adding a general person to the system by entering all their details.
Sort an array of employees in a specific station by ID, salary, or age.

Perform a binary search for an employee in a specific station if sorting was done previously.

Add random expenses to all customers in a specific station chosen by the user.

Find the station with the highest profits by checking which station's total customer expenses are the highest.
