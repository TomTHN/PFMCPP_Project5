/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 2) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 3) write the name of your class where it says "OwnerClass"
 
 4) write wrapper classes for each type similar to how it was shown in the video
 
 5) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

6) If you have a class that has a nested class in it, and an instantiation of that nested class as a member variable, 
    - you do not need to write a Wrapper for that nested class
    - you do not need to replace that nested instance with a wrapped instance.
    If you want an explanation, message me in Slack

7) If you were using any UDTs as function arguments like this:
*/
#if false
void someMemberFunction(Axe axe);
#endif
/*
  Pass those arguments by Reference now that you know what references are (Project 6 Part 2).
*/
#if false
void someMemberFunction(Axe& axe);
#endif
/*
If you aren't modifying the passed-in object inside the function, pass by 'const reference'.
Marking a function parameter as 'const' means that you are promising that the parameter will not be modified.
Additionally, you can mark class member functions as 'const'
If you do this, you are promising that the member function will not modify any member variables.

Mark every member function that is not modifying any member variables as 'const'
*/
#if false
//a function where the argument is passed by const-ref
void someMemberFunction(const Axe& axe);

//a member function that is marked const, meaning it will not modify any member variables of the 'Axe' class.
void Axe::aConstMemberFunction() const { }
#endif
/*
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 Clear any warnings about exit-time-destructors.
 Suppress them by adding -Wno-exit-time-destructors to the .replit file with the other warning suppression flags
 */




#include <iostream>
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
    };

    float withdrawMoney(Customer customer, float moneyToWithdraw); //returns updated bank balance
    float depositMoney(Customer customer, float moneyToDeposit); //returns updated bank balance
    float takeCredit(Customer customer, float amountCredit, float periodToRepay); //returns interest rate
    void refillATM(int amountWithdrawFiftyDollar);
    void printAmountCounters();
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
    };

    void rideDownhill();
    bool eatLunch(); //returns false if person is still hungry     
    void haveGoodTime();
    void fillPickupTruckWithBikes(int amountOfBikes);
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
    Bank newBank;
    Bank::Customer tom;
    BikePark newBikePark;
    BikePark::Bike newBike;
    Pedals newPedals;
    std::cout << std::endl;
    HolidayArea newHolidayArea;
    std::cout << std::endl;
    EuropeanCentralBank newEuropeanCentralBank;
    std::cout << std::endl;

    newBank.depositMoney(tom, 2000.50f);
    newBank.withdrawMoney(tom, 500.0f);
    newBank.refillATM(10);
    tom.cancelBankAccount(false);
    tom.talkEmployee("I need to talk to your boss");
    tom.robBank(true);

    std::cout << "Number of counters: " << newBank.numBankCounters << " (print directly)" << std::endl;
    newBank.printAmountCounters();
    
    newBikePark.eatLunch();
    newBikePark.haveGoodTime();
    newBikePark.rideDownhill();
    newBikePark.fillPickupTruckWithBikes(7);
    newBike.inflateTires(27.0f, 20.0f);
    newBike.repair();
    newBike.setupSuspension(95.4f, 25);

    std::cout << "Wheel size: " << newBike.wheelSize << " (print directly)" << std::endl;
    newBike.printwheelSize();

    float accelerateBikeReturn = newPedals.accelerateBike(8.5f, 15.0f);
    newPedals.assemble();
    newPedals.turn();
    newPedals.hitShin(10);

    std::cout << "You need to drive " << accelerateBikeReturn << " km/h faster!" << std::endl;

    newHolidayArea.rentBike(100, 6);
    newHolidayArea.buyTicketBikePark(2, 39);
    
    newEuropeanCentralBank.increasKeyInterestRate(0.05f);
    newEuropeanCentralBank.printMoney(150.00f);

    std::cout << "good to go!" << std::endl;
    std::cout << std::endl;
}
