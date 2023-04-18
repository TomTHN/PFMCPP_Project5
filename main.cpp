/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3.
       you will learn how to take code from existing projects and migrate only what you need to new projects
       you will learn how to write code that doesn't leak as well as how to refactor. 

NOTE: there are 2 sets of instructions:
       One for if you completed project 3
       One for if you skipped project 3.

 Destructors

===============================================================     
 If you completed Project 3:
 
 1) Copy 3 of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
    Choose the classes that contained nested classes.  Include the nested classes when you copy them over.

 2) move all of your implementations of all functions to OUTSIDE of the class.

 3) add destructors
        make the destructors do something like print out the name of the class.
===============================================================
If you skipped Project 3:
write 3 UDTs below that EACH have: 
        5 member variables
            the member variable names and types should be relevant to the work the UDT will perform.
            pick properties that can be represented with 'int float double bool char std::string'
        3 member functions with an arbitrary number of parameters
            give some of those parameters default values.
        constructors that initialize some of these member variables
            the remaining member variables should be initialized in-class
        for() or while() loops that modify member variables
 1) 2 of your 3 UDTs need to have a nested UDT.
    this nested UDT should fulfill the same requirements as above:
        5 member variables  
        3 member functions
        constructors and loops.
        
 2) Define your implementations of all functions OUTSIDE of the class. 
 NO IN-CLASS IMPLEMENTATION ALLOWED
 3) add destructors to all of your UDTs
        make the destructors do something like print out the name of the class.
===============================================================

 4) add 2 new UDTs that use only the types you copied above as member variables.

 5) add 2 member functions that use your member variables to each of these new UDTs

 6) Add constructors and destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 7) copy over your main() from the end of Project3 
        get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.
 
 8) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
       call their member functions.
 
 9) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.

 you can resolve any [-Wdeprecated] warnings by adding -Wno-deprecated to list of compiler arguments in the .replit file. all of the "-Wno" in that file are compiler arguments.
 You can resolve any [-Wpadded] warnings by adding -Wno-padded to the list of compiler arguments in the .replit file. all of the "-Wno" in that file are compiler arguments.

 Ignore the Atomic.h and LeakedObjectDetector.h files for now.
 You will use those in Part 3 of this project.

 */

/*
 copied UDT 1:
 */
struct Bank
{
    Bank();

    int numATM;
    int amountEmployees {20};
    int amountSecurityCameras {5};
    int numBankCounters = 5;
    int numCustomersDay = 1000;
    float moneyATM {40000.00f};

    struct Customer
    {
        Customer();

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
};

Bank::Bank() : numATM(3)
{
    std::cout << std::endl << "Bank being constructed!" << std::endl;
}

Bank::Customer::Customer() : customerNumber{12345678}, age{45}
{
    std::cout << "Bank::Customer being constructed!" << std::endl;
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
/*
 copied UDT 2:
 */
struct BikePark
{
    BikePark();

    int amountTracks;
    float hightMountain; //meters
    int numLifts = 5;
    int amountBlackDiamontTracks = 10;
    int accidentsYear = 700;
    int bikeMaximum {6};

    struct Bike
    {
        Bike();

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

BikePark::Bike::Bike() : sag{15}
{
    std::cout << "BikePark::Bike being constructed!" << std::endl;
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
    for(int addedBikes = 0; amountOfBikes > addedBikes; ++addedBikes)
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
/*
 copied UDT 3:
 */
struct Pedals
{
    Pedals();

    std::string brand {"RaceFace"};
    int size = 10;
    std::string color {"black"};
    std::string material = "titanium";
    int amountTorque = 15; //Nm

    void assemble();
    void turn();
    float accelerateBike(float currentSpeed, float targetSpeed); // returns updated speed
    void hitShin(int hitsTillBlood = 10);
};

Pedals::Pedals()
{
    std::cout << "Pedals being constructed!" << std::endl;
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

/*
 new UDT 5:
 with 2 member functions
 */

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
    std::cout << "good to go!" << std::endl;
}
