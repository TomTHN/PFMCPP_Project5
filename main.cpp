/*
 Project 5: Part 4 / 4
 video: Chapter 3 Part 7

 Create a branch named Part4
 
 Don't #include what you don't use
 
 1) Your task is to refactor your Chapter 3 Part 4 task into separate source and header files.
         Add files via the pane on the left.
 
 2) Put all of your declarations for each class in .h files
         One header file per class ( i.e. Raider.h for a class named "Raider" )
         Don't forget the '#pragma once'
 
 3) Put all of your implementations in .cpp files.
         one cpp file per class ( i.e. Raider.cpp for a class named "Raider" )
 
 4) Put all of your Wrapper classes in a single Wrappers.h file
         if you implemented your wrapper class functions in-class, you'll need to move them to Wrappers.cpp, which goes along with instruction 5): 
 
 5) NO IN-CLASS IMPLEMENTATION ALLOWED.
         the only exception is the existing Atomic.h and LeakedObjectDetector.h
        Chances are extremely high that you implemented your 
        wrapper class functions in-class, because that is what 
        everyone does after watching the video where I implemented 
        them in-class.
 
 6) for every .cpp file you have to make, insert it into the .replit file after 'main.cpp'.  Don't forget the spaces between file names.
 If you need help with this step, send me a DM.

 7) When you add the #include statements for your refactored source files into main.cpp: 
        '#include "Wrappers.h"' should be the first file that you include after LeakedObjectDetector.h
 
 8) Go through every cpp file and header file. check all function implementations for the following:
        Can this function argument be declared as 'const'? 
        Can this function be declared as 'const'?
        You learned about 'const' function arguments and 'const' functions in Project 5 Part 3
        As a refresher:
            If you aren't modifying the passed-in object inside the function, pass by 'const reference'.
            Marking a function parameter as 'const' means that you are promising that the parameter will not be modified.
            Additionally, you can mark class member functions as 'const'
            If you do this, you are promising that the member function will not modify any member variables.

        Mark every member function that is not modifying any member variables as 'const'
        Mark every function parameter that is not modified inside the function as 'const'
*/
#if false
//a function where the argument is passed by const-ref.
void Foo::someMemberFunction(const Axe& axe);

//a member function that is marked const, meaning it will not modify any member variables of the 'Axe' class.
void Axe::aConstMemberFunction() const { }
#endif
/*
 9) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Remember, your Chapter 3 Part 4 task worked when it was all in one file. so you shouldn't need to edit any of it.  
         just split it up into source files and provide the appropriate #include directives.
         tip: you cannot forward-declare nested types!  
         The file that a nested type is defined in MUST be included wherever that nested type is written.
 */




#include <iostream>
#include "LeakedObjectDetector.h"
/*
 copied UDT 1:
 */
struct Bank
{
    Bank();
    ~Bank();

    int numATM;
    int amountEmployees {20};
    int amountSecurityCameras {5};
    int numBankCounters = 5;
    int numCustomersDay = 1000;
    float moneyATM {40000.00f};

    struct Customer
    {
        Customer();
        ~Customer();

        int customerNumber, age;
        std::string gender = "male";
        float bankBalance {4550.60f};
        int memberTime  = 600; //days

        void cancelBankAccount(bool state);
        std::string talkEmployee(std::string question);
        void robBank(bool decision);

        JUCE_LEAK_DETECTOR(Customer)
    };

    float withdrawMoney(Customer customer, float moneyToWithdraw); //returns updated bank balance
    float depositMoney(Customer customer, float moneyToDeposit); //returns updated bank balance
    float takeCredit(Customer customer, float amountCredit, float periodToRepay); //returns interest rate
    void refillATM(int amountWithdrawFiftyDollar);
    void printAmountCounters();

    JUCE_LEAK_DETECTOR(Bank)
};

Bank::Bank() : numATM(3)
{
    std::cout << "Bank being constructed!" << std::endl;
}

Bank::~Bank()
{
    std::cout << "Bank being destructed!" << std::endl;
}

Bank::Customer::Customer() : customerNumber{12345678}, age{45}
{
    std::cout << "Bank::Customer being constructed!" << std::endl;
}

Bank::Customer::~Customer()    
{
    std::cout << "Bank::Customer being destructed!" << std::endl;
}

void Bank::Customer::cancelBankAccount(bool state)
{
    if(state)
    {
        std::cout << "I want to cancel my bank account!" << std::endl;
    }
}

std::string Bank::Customer::talkEmployee(std::string question)
{
    std::cout << question << std::endl;
    return question;
}

void Bank::Customer::robBank(bool desicion)
{
    if(desicion)
    {
        std::cout << "Ladies and gentlemen, this is a robbery!" << std::endl;
    }
}

float Bank::withdrawMoney(Customer customer, float moneyToWithdraw)
{
    float updatedBankBalance = customer.bankBalance - moneyToWithdraw;
    std::cout << "Your new bank balance is: " << updatedBankBalance << "."  << std::endl;
    return updatedBankBalance;
}

float Bank::depositMoney(Customer customer, float moneyToDeposit)
{
    float updatedBankBalance = customer.bankBalance + moneyToDeposit;
    std::cout << "Your new bank balance is: " << updatedBankBalance << "." << std::endl;
    return updatedBankBalance;
}

float Bank::takeCredit(Customer customer, float amountCredit, float periodToRepay)
{
    customer.bankBalance += amountCredit;
    return amountCredit / periodToRepay;
}

void Bank::refillATM(int amountWithdrawFiftyDollar)
{
    for (int i = 0; i < amountWithdrawFiftyDollar; ++i)
    {
        moneyATM -= 50.00f;
        if(moneyATM <= 1000.00f)
        {
            std::cout << "Only " << moneyATM << " Dollar left. Please refill ATM" << std::endl;
        }
    }  
}

void Bank::printAmountCounters()
{
    std::cout << "Number of counters: " << this->numBankCounters << " (print function)" << std::endl;
}

struct BankWrapper
{
    BankWrapper(Bank* ptr) : PointerToBank (ptr) { }
    ~BankWrapper() { delete PointerToBank; }

    Bank* PointerToBank = nullptr;
};

/*
 copied UDT 2:
 */
struct BikePark
{
    BikePark();
    ~BikePark();

    int amountTracks;
    float hightMountain; //meters
    int numLifts = 5;
    int amountBlackDiamontTracks = 10;
    int accidentsYear = 700;
    int bikeMaximum {6};

    struct Bike
    {
        Bike();
        ~Bike();

        bool hasFullSuspension = true;
        std::string brand = "GT";
        std::string color = "red";
        float wheelSize = 27.5f;
        float ageBike = 4.5f;
        float pressureSuspension = 95.4f;
        int sag;

        float inflateTires(float targetPressureTire, float currentPressur); //Returns updated pressure 
        int setupSuspension(float targetPressure, int targetSag);
        void repair();
        void printwheelSize();

        JUCE_LEAK_DETECTOR(Bike)
    };

    void rideDownhill();
    bool eatLunch(); //returns false if person is still hungry     
    void haveGoodTime();
    void fillPickupTruckWithBikes(int amountOfBikes);

    JUCE_LEAK_DETECTOR(BikePark)
};

BikePark::BikePark() : amountTracks{23}, hightMountain{3400}
{
    std::cout << "BikePark being constructed!" << std::endl;
}

BikePark::~BikePark()
{
    std::cout << "BikePark being destructed!" << std::endl;
}

BikePark::Bike::Bike() : sag{15}
{
    std::cout << "BikePark::Bike being constructed!" << std::endl;
}

BikePark::Bike::~Bike()
{
    std::cout << "BikePark::Bike being destructed!" << std::endl;
}

float BikePark::Bike::inflateTires(float targetPressureTire, float currentPressur)
{
    return targetPressureTire - currentPressur;
}

int BikePark::Bike::setupSuspension(float targetPressure, int targetSag)
{
    pressureSuspension = targetPressure;
    std::cout << "my sag is " << sag << " cm but I need " << targetSag << " cm!" << std::endl;
    return targetSag - sag;
}

void BikePark::Bike::repair()
{
    
}

void BikePark::rideDownhill()
{
    
}

bool BikePark::eatLunch()
{
    return true;
}

void BikePark::haveGoodTime()
{
    
}

void BikePark::fillPickupTruckWithBikes(int amountOfBikes)
{
    for(int addedBikes = 0; addedBikes < amountOfBikes; ++addedBikes)
    {
        if(addedBikes == bikeMaximum)
        {
            std::cout << "Truck is full!" << std::endl;
        }   
        else
        {
            std::cout << "Still space!" << std::endl;
        }
    }
}

void BikePark::Bike::printwheelSize()
{
    std::cout << "Wheel size: " << this->wheelSize << " (print function)" << std::endl;
}

struct BikeParkWrapper
{
    BikeParkWrapper(BikePark* ptr) : PointerToBikePark (ptr) { }
    ~BikeParkWrapper() { delete PointerToBikePark; }

    BikePark* PointerToBikePark = nullptr;
};
/*
 copied UDT 3:
 */
struct Pedals
{
    Pedals();
    ~Pedals();

    std::string brand {"RaceFace"};
    int size = 10;
    std::string color {"black"};
    std::string material = "titanium";
    int amountTorque = 15; //Nm

    void assemble();
    void turn();
    float accelerateBike(float currentSpeed, float targetSpeed); // returns updated speed
    void hitShin(int hitsTillBlood);

    JUCE_LEAK_DETECTOR(Pedals)
};

Pedals::Pedals()
{
    std::cout << "Pedals being constructed!" << std::endl;
}

Pedals::~Pedals()
{
    std::cout << "Pedals being destructed!" << std::endl;
}

void Pedals::assemble()
{
    
}

void Pedals::turn()
{
    
}

float Pedals::accelerateBike(float currentSpeed, float targetSpeed)
{
    return targetSpeed - currentSpeed;
}

void Pedals::hitShin(int hitsTillBlood = 10)
{
    for(int hit = 0; hit < hitsTillBlood; ++hit)
    {
        std::cout << hit << std::endl;
            
        if(hit == 9)
        {
            std::cout << "You´re bleeding" << std::endl;
        }
    }
}

struct PedalsWrapper
{
    PedalsWrapper(Pedals* ptr) : PointerToPedals (ptr) { }
    ~PedalsWrapper() { delete PointerToPedals; }

    Pedals* PointerToPedals = nullptr;
};

/*
 new UDT 4:
 with 2 member functions
 */
struct HolidayArea
{
    HolidayArea();
    ~HolidayArea();

    BikePark holidayBikePark;
    BikePark::Bike rentalBike;

    void rentBike(int pricePerDay, int rentalPeriod);
    void buyTicketBikePark(int howManyDays, int ticketPrice);

    JUCE_LEAK_DETECTOR(HolidayArea)
};

HolidayArea::HolidayArea()
{
    std::cout << "Holiday area being constructed!" << std::endl;
    rentalBike.inflateTires(25.00f, 20.00f);
}

HolidayArea::~HolidayArea()
{
    std::cout << "Holiday area being destructed!" << std::endl;
    rentalBike.repair();
}

void HolidayArea::rentBike(int pricePerDay, int rentalPeriod)
{
    int price = pricePerDay * rentalPeriod;
    if(500 < price)
    {
        rentalBike.hasFullSuspension = true;
    }
    else
    {
        rentalBike.hasFullSuspension = false;
    }    
}

void HolidayArea::buyTicketBikePark(int howManyDays, int ticketPrice)
{
    std::cout << "You have to pay " << howManyDays * ticketPrice << "$" << std::endl;
}

struct HolidayAreaWrapper
{
    HolidayAreaWrapper(HolidayArea* ptr) : PointerToHolidayArea (ptr) { }
    ~HolidayAreaWrapper() { delete PointerToHolidayArea; }

    HolidayArea* PointerToHolidayArea = nullptr;
};

/*
 new UDT 5:
 with 2 member functions
 */
struct EuropeanCentralBank
{
    EuropeanCentralBank();
    ~EuropeanCentralBank();

    Bank myBank;
    Bank::Customer guy;
    float keyInterestRate {1.02f};

    void increasKeyInterestRate(float increaseKeyInterestRate);
    void printMoney(float amountInBillion);

    JUCE_LEAK_DETECTOR(EuropeanCentralBank)
};

EuropeanCentralBank::EuropeanCentralBank()
{
    std::cout << "European central bank being constructed!" << std::endl;
}

EuropeanCentralBank::~EuropeanCentralBank()
{
    std::cout << "European central bank being destructed!" << std::endl;
}

void EuropeanCentralBank::increasKeyInterestRate(float increaseKeyInterestRate)
{
    keyInterestRate += increaseKeyInterestRate;
}

void EuropeanCentralBank::printMoney(float amountInBillion)
{
    if(100.00f < amountInBillion)
    {
        std::cout << "inflation is rising" << std::endl;
    }
} 

struct EuropeanCentralBankWrapper
{
    EuropeanCentralBankWrapper(EuropeanCentralBank* ptr) : PointerToEuropeanCentralBank (ptr) { }
    ~EuropeanCentralBankWrapper() { delete PointerToEuropeanCentralBank; }

    EuropeanCentralBank* PointerToEuropeanCentralBank = nullptr;
};

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

#include <iostream>
int main()
{
    BankWrapper newBank(new Bank());
    Bank::Customer tom;
    BikeParkWrapper newBikePark(new BikePark());
    BikePark::Bike newBike;
    PedalsWrapper newPedals(new Pedals());
    std::cout << std::endl;
    HolidayAreaWrapper newHolidayArea(new HolidayArea());
    std::cout << std::endl;
    EuropeanCentralBankWrapper newEuropeanCentralBank(new EuropeanCentralBank());
    std::cout << std::endl;

    newBank.PointerToBank->depositMoney(tom, 2000.50f);
    newBank.PointerToBank->withdrawMoney(tom, 500.0f);
    newBank.PointerToBank->refillATM(10);
    tom.cancelBankAccount(false);
    tom.talkEmployee("I need to talk to your boss");
    tom.robBank(true);

    std::cout << "Number of counters: " << newBank.PointerToBank->numBankCounters << " (print directly)" << std::endl;
    newBank.PointerToBank->printAmountCounters();
    
    newBikePark.PointerToBikePark->eatLunch();
    newBikePark.PointerToBikePark->haveGoodTime();
    newBikePark.PointerToBikePark->rideDownhill();
    newBikePark.PointerToBikePark->fillPickupTruckWithBikes(7);
    newBike.inflateTires(27.0f, 20.0f);
    newBike.repair();
    newBike.setupSuspension(95.4f, 25);

    std::cout << "Wheel size: " << newBike.wheelSize << " (print directly)" << std::endl;
    newBike.printwheelSize();

    float accelerateBikeReturn = newPedals.PointerToPedals->accelerateBike(8.5f, 15.0f);
    newPedals.PointerToPedals->assemble();
    newPedals.PointerToPedals->turn();
    newPedals.PointerToPedals->hitShin(10);

    std::cout << "You need to drive " << accelerateBikeReturn << " km/h faster!" << std::endl;

    newHolidayArea.PointerToHolidayArea->rentBike(100, 6);
    newHolidayArea.PointerToHolidayArea->buyTicketBikePark(2, 39);
    
    newEuropeanCentralBank.PointerToEuropeanCentralBank->increasKeyInterestRate(0.05f);
    newEuropeanCentralBank.PointerToEuropeanCentralBank->printMoney(150.00f);

    std::cout << "good to go!" << std::endl;
    std::cout << std::endl;
}
