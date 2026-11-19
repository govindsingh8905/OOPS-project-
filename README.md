# Vehicle / Car Rental Management System (C++17)

A robust, enterprise-grade, terminal-based Vehicle Rental Management System written in modern **C++17**. The project is strictly terminal-only (no GUI, no web frontend, no external database servers) and is architected from the ground up to showcase **Object-Oriented Programming (OOP) design patterns**, memory safety with smart pointers, and text-based persistent file handling.

---

## Table of Contents

- [Key Features](#key-features)
- [Strict Terminal-Only Architecture](#strict-terminal-only-architecture)
- [Object-Oriented Programming (OOP) Implementation](#object-oriented-programming-oop-implementation)
- [UML Class Diagram](#uml-class-diagram)
- [Project Directory Structure](#project-directory-structure)
- [Compilation & Execution Instructions](#compilation--execution-instructions)
- [Default Credentials](#default-credentials)
- [Menu Flow & Walkthrough](#menu-flow--walkthrough)
- [Data Storage & File Formats](#data-storage--file-formats)

---

## Key Features

1. **Terminal-First User Interface**:
   - Clean, professional ASCII borders, headers, subheaders, and aligned tabular formats.
   - Cross-platform screen clearing and smooth interactive prompts.
   - Comprehensive input sanitization; graceful recovery from illegal types (characters instead of integers, out-of-bounds choices).

2. **Admin Operations**:
   - Add new vehicles (Cars or Bikes) with category-specific attributes (Seats, Fuel, AC vs. Engine CC, Bike Type).
   - Remove vehicles (with safety checks preventing removal of currently rented vehicles).
   - Update vehicle details (Brand, Model, Rental Rate).
   - Real-time fleet overview: All Vehicles, Available Vehicles, Currently Rented Vehicles.
   - Registered Customer directory review.
   - Comprehensive Rental logs inspection.
   - Dynamic Revenue & Fleet Utilization report with Car vs. Bike revenue breakdown.

3. **Customer Operations**:
   - New user registration with duplicate email validation and ID generation.
   - Secure customer authentication with driving license tracking.
   - Vehicle fleet search by Category (Car/Bike), Brand substring, or Maximum Daily Rate.
   - Dynamic booking engine with instant quotes, date calculation, and confirmation checkpoints.
   - Seamless Vehicle Return with late-return surcharge computation.
   - Personal Rental History tracking and Profile viewer.

4. **Simulated Payment Module**:
   - Cash and simulated UPI payment options with transaction ID generation (`TXN1001`+).
   - Instant formatted payment and booking receipts.

5. **Persistent Storage**:
   - Text file persistence (`data/vehicles.txt`, `data/customers.txt`, `data/rentals.txt`, `data/payments.txt`).
   - Auto-seeding of sample fleet and users if launched on an empty workspace.

---

## Strict Terminal-Only Architecture

- **Zero External GUI/Web Dependencies**: Built using standard ISO C++17 standard library components (`<iostream>`, `<memory>`, `<vector>`, `<string>`, `<map>`, `<fstream>`, `<iomanip>`, `<chrono>`, `<thread>`).
- **No Database Engine Required**: All records are serialized and deserialized using structured text pipes (`|`) with crash-proof exception handling.
- **Cross-Platform Compatibility**: Tested and fully compatible with macOS, Linux, and Windows (PowerShell/CMD).

---

## Object-Oriented Programming (OOP) Implementation

| OOP Concept | Implementation Details | Location in Code |
| :--- | :--- | :--- |
| **Classes & Objects** | Dedicated classes with focused responsibilities: `Vehicle`, `Car`, `Bike`, `Customer`, `Admin`, `Rental`, `Payment`, `RentalSystem`, `FileHandler`, `UIUtils`. | All `.h` and `.cpp` files |
| **Encapsulation** | All member variables are `private` or `protected`. Public getters and setters with validation protect data integrity. | `Vehicle.h`, `Customer.h`, `Rental.h`, `Payment.h` |
| **Inheritance** | Hierarchical design where `Car` and `Bike` inherit from the abstract base class `Vehicle`. | `Car.h:7`, `Bike.h:7` |
| **Abstraction** | `Vehicle` acts as an abstract base class containing pure virtual functions (`getType() = 0`, `calculateRent() = 0`, `displayDetails() = 0`, `serialize() = 0`, `clone() = 0`). | `Vehicle.h:20-24` |
| **Runtime Polymorphism** | Virtual method dispatching via base class smart pointers (`std::shared_ptr<Vehicle>`). Calling `v->calculateRent(days)` or `v->serialize()` invokes the derived class implementation at runtime. | `RentalSystem.cpp`, `Vehicle.h` |
| **Compile-Time Polymorphism** | Function overloading for flexible business rules: `Car::calculateRent(days)` vs `Car::calculateRent(days, withInsurance)`; `Rental::calculateCharges()` vs `Rental::calculateCharges(extraDays, pricePerDay)`; `FileHandler::appendRecord()`. | `Car.h:21`, `Bike.h:20`, `Rental.h:32-33`, `FileHandler.h:30-31` |
| **Operator Overloading** | Overloaded `operator==` for identity comparison; overloaded `operator<<` (friend function) for formatted streaming output. | `Vehicle.cpp:32-42`, `Customer.cpp:46-56`, `Rental.cpp:45-56`, `Payment.cpp:47-52` |
| **Constructors & Destructors** | Parameterized and default constructors using initialization lists. `Vehicle` defines a `virtual ~Vehicle() = default;` to ensure proper destruction of polymorphic derived objects. `RentalSystem` destructor auto-saves all records on shutdown. | `Vehicle.cpp`, `RentalSystem.cpp:18` |
| **Composition & Association** | `RentalSystem` **has-a** collection of vehicles, customers, rentals, and payments (Composition). `Rental` associates `Customer` and `Vehicle` via their unique identifiers (`customerId`, `vehicleId`) without tight coupling (Association). | `RentalSystem.h:20-25`, `Rental.h:11-13` |
| **Smart Pointers** | Memory safety via `std::shared_ptr<Vehicle>` and `std::unique_ptr<Vehicle>` in polymorphic collections, preventing memory leaks and avoiding raw pointer hazards. | `RentalSystem.h`, `Vehicle.h` |
| **File Handling** | Persistent stream handling (`std::ifstream`, `std::ofstream`) with record serialization and defensive parsing. | `FileHandler.cpp` |

---

## UML Class Diagram

```
                             +------------------------+
                             |    <<abstract>>        |
                             |        Vehicle         |
                             +------------------------+
                             |# id: string            |
                             |# brand: string         |
                             |# model: string         |
                             |# pricePerDay: double   |
                             |# available: bool       |
                             +------------------------+
                             |+ virtual getType() = 0 |
                             |+ virtual calcRent() = 0|
                             |+ virtual serialize()=0 |
                             |+ virtual clone() = 0   |
                             |+ operator==()          |
                             |+ operator<<()          |
                             +------------------------+
                                         ^
                                         |
                       +-----------------+-----------------+
                       |                                   |
           +-----------------------+           +-----------------------+
           |          Car          |           |         Bike          |
           +-----------------------+           +-----------------------+
           |- seats: int           |           |- engineCC: int        |
           |- fuelType: string     |           |- bikeType: string     |
           |- hasAC: bool          |           +-----------------------+
           +-----------------------+           |+ getType(): string    |
           |+ getType(): string    |           |+ calcRent(days): dbl  |
           |+ calcRent(days): dbl  |           |+ calcRent(d,helm): dbl|
           |+ calcRent(d,ins): dbl |           |+ serialize(): string  |
           |+ serialize(): string  |           +-----------------------+
           +-----------------------+

+------------------+         +------------------+         +------------------+
|     Customer     |         |      Rental      |         |     Payment      |
+------------------+         +------------------+         +------------------+
|- id: string      |         |- rentalId: string|         |- txnId: string   |
|- name: string    |         |- custId: string  |         |- rentalId: string|
|- phone: string   |         |- vehicleId: str  |         |- custId: string  |
|- email: string   |         |- days: int       |         |- amount: double  |
|- password: string|         |- amount: double  |         |- method: string  |
|- license: string |         |- startDate: str  |         |- date: string    |
+------------------+         |- endDate: string |         +------------------+
|+ validatePwd()   |         |- returned: bool  |         |+ generateReceipt()|
|+ serialize()     |         |- returnDate: str |         |+ serialize()     |
|+ operator==()    |         +------------------+         +------------------+
+------------------+         |+ markReturned()  |
                             |+ calcCharges()   |
                             |+ serialize()     |
                             +------------------+

                             +------------------------+
                             |      RentalSystem      |
                             +------------------------+
                             |- vehicles: vector<ptr> | <>--- (Composition: Vehicles)
                             |- customers: vector<C>  | <>--- (Composition: Customers)
                             |- rentals: vector<R>    | <>--- (Composition: Rentals)
                             |- payments: vector<P>   | <>--- (Composition: Payments)
                             |- admin: Admin          |
                             +------------------------+
                             |+ run()                 |
                             |+ adminDashboard()      |
                             |+ customerDashboard()   |
                             |+ rentVehicle()         |
                             |+ returnVehicle()       |
                             |+ processPayment()      |
                             |+ saveAllData()         |
                             |+ loadAllData()         |
                             +------------------------+
                                         |
                                         v
                         +-------------------------------+
                         |   FileHandler   |   UIUtils   |
                         +-------------------------------+
                         | Static utilities for I/O and  |
                         | terminal ASCII formatting     |
                         +-------------------------------+
```

---

## Project Directory Structure

```
OOPS/
├── Makefile                     # C++17 build automation file
├── README.md                    # Project documentation & architecture specs
├── data/                        # Persistent text data files
│   ├── customers.txt            # Registered customer accounts
│   ├── payments.txt             # Payment transaction records
│   ├── rentals.txt              # Active and completed rental records
│   └── vehicles.txt             # Fleet specifications and availability
├── include/                     # C++ Header files (.h)
│   ├── Admin.h                  # Administrator entity & authentication
│   ├── Bike.h                   # Derived Bike class
│   ├── Car.h                    # Derived Car class
│   ├── Customer.h               # Customer entity & password validation
│   ├── FileHandler.h            # Static persistence & directory manager
│   ├── Payment.h                # Payment entity & receipt generator
│   ├── Rental.h                 # Rental contract & late-fee calculations
│   ├── RentalSystem.h           # Main controller orchestrating business flow
│   ├── UIUtils.h                # Terminal tables, ASCII headers, input cleaners
│   └── Vehicle.h                # Abstract base class
└── src/                         # C++ Source implementations (.cpp)
    ├── Admin.cpp
    ├── Bike.cpp
    ├── Car.cpp
    ├── Customer.cpp
    ├── FileHandler.cpp
    ├── Payment.cpp
    ├── Rental.cpp
    ├── RentalSystem.cpp
    ├── UIUtils.cpp
    ├── Vehicle.cpp
    └── main.cpp                 # Application entry point
```

---

## Compilation & Execution Instructions

### Prerequisites
- Any C++17 compatible compiler: `g++` (version 7+), `clang++` (version 5+), or Apple Clang.
- `make` utility.

### Option 1: Using the Automated Makefile (Recommended)
```bash
# Clone or navigate to the directory
cd /Users/govindsingh/OOPS

# Build the binary
make

# Run the program
./rental_system

# Or build and launch directly
make run

# Clean build artifacts
make clean
```

### Option 2: Direct Compilation with g++
```bash
cd /Users/govindsingh/OOPS
g++ -std=c++17 -Wall -Wextra -I include src/*.cpp -o rental_system
./rental_system
```

---

## Default Credentials

### Administrator Account
- **Username**: `admin`
- **Password**: `admin123`

### Pre-configured Sample Customers
| Customer ID | Name | Email | Password | License |
| :--- | :--- | :--- | :--- | :--- |
| `C1001` | Rahul Sharma | `rahul@email.com` | `pass123` | `DL1420110012345` |
| `C1002` | Priya Singh | `priya@email.com` | `pass456` | `DL0420180098765` |

*(You can also use option 2 from the welcome screen to register any new customer account at runtime).*

---

## Menu Flow & Walkthrough

### 1. Welcome Screen
```text
=======================================================
       VEHICLE RENTAL MANAGEMENT SYSTEM
=======================================================
       Welcome to our Rental Service!
=======================================================

  1. Admin Login
  2. Customer Registration
  3. Customer Login
  4. Exit

-------------------------------------------------------
Enter your choice: 
```

### 2. Vehicle Listing Table
```text
+----------+------------------+------------------+--------+-------------+-----------+
| ID       | Brand            | Model            | Type   | Price/Day   | Status    |
+----------+------------------+------------------+--------+-------------+-----------+
| V101     | Tata             | Nexon            | Car    | Rs. 1500    | Available |
| V102     | Honda            | City             | Car    | Rs. 2000    | Available |
| V103     | Hyundai          | Creta            | Car    | Rs. 2500    | Available |
| V104     | Maruti           | Swift            | Car    | Rs. 1200    | Available |
| V105     | Toyota           | Fortuner         | Car    | Rs. 4000    | Available |
| V106     | Royal Enfield    | Classic 350      | Bike   | Rs. 800     | Available |
| V107     | KTM              | Duke 200         | Bike   | Rs. 600     | Available |
| V108     | Honda            | Activa 6G        | Bike   | Rs. 350     | Available |
| V109     | Yamaha           | R15 V4           | Bike   | Rs. 750     | Available |
| V110     | Bajaj            | Pulsar NS200     | Bike   | Rs. 500     | Available |
+----------+------------------+------------------+--------+-------------+-----------+
```

### 3. Booking Quotation & Official Receipts
```text
==================================================
               BOOKING QUOTATION
==================================================
  Customer       : Rahul Sharma (C1001)
  Vehicle        : Tata Nexon
  Type           : Car
  Price Per Day  : Rs. 1500
  Rental Days    : 3
--------------------------------------------------
  Total Amount   : Rs. 4500.00
==================================================
Confirm Booking? (Y/N): Y

--------------------------------------------------
               PAYMENT CHECKOUT
--------------------------------------------------
  Amount Due: Rs. 4500.00
  Select Payment Mode:
    1. Cash
    2. UPI
    3. Cancel Payment
Enter your choice: 2
  UPI Payment Gateway Simulation:
  Enter UPI ID: rahul@upi
  Contacting Bank & Processing UPI Payment..... Done!

==================================================
              PAYMENT RECEIPT
==================================================
  Transaction ID : TXN1001
  Rental ID      : R1001
  Customer ID    : C1001
  Amount         : Rs. 4500.00
  Payment Method : UPI
  Date           : 2026-11-19
==================================================

=======================================================
                 OFFICIAL BOOKING RECEIPT              
=======================================================
  Rental ID        : R1001
  Customer ID      : C1001
  Customer Name    : Rahul Sharma
  Phone Number     : 9876543210
  Vehicle ID       : V101
  Vehicle Details  : Tata Nexon (Car)
  Rental Period    : 2026-11-19 to 2026-11-22 (3 days)
  Rate Per Day     : Rs. 1500
  Total Paid       : Rs. 4500.00
  Booking Status   : CONFIRMED & ACTIVE
=======================================================
```

---

## Data Storage & File Formats

All data files are stored in the `data/` directory using pipe-delimited format:

1. **`vehicles.txt`**:
   - Car: `id|brand|model|pricePerDay|available(1/0)|Car|seats|fuelType|hasAC(1/0)`
   - Bike: `id|brand|model|pricePerDay|available(1/0)|Bike|engineCC|bikeType`
2. **`customers.txt`**:
   - `id|name|phone|email|password|licenseNumber`
3. **`rentals.txt`**:
   - `rentalId|customerId|vehicleId|days|totalAmount|startDate|endDate|isReturned(1/0)|returnDate`
4. **`payments.txt`**:
   - `transactionId|rentalId|customerId|amount|paymentMethod|paymentDate`

