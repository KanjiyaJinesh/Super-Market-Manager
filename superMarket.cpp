#include <bits/stdc++.h>
#include<time.h>
using namespace std;

struct dataset1
{
    long id;
    string name;
    float rate;
    int qq;
};
struct dataset2
{
    long id;
    string name;
    float points;
};
long rword(int n)
{
    long rand_id=0;
    while(n--)
    {
        rand_id=rand_id + pow(10,n)*(rand()%10);
    }
    return rand_id;
}
struct item
{
    long item_ID;
    string Name;
    float Rate;
    int Quantity;
    float Amount;
    item* next;
};
struct customer
{
    long customer_ID;
    string Name;
    float Points;
    customer* next;
};
class inventory
{
    private:
    static item* item_list[15];
    protected:
    void Add_item(long,string,float,int);        // Add item with Id, name, rate, and quantity.
    void Delete_item(long);                      // Delete item with given ID. 
    void Update_item(long,float,int);            // Update rate and quantity of item with given ID.
    int Change_quantity(long,int);
    
    public:
    void make_ItemList()
    {
        for(int i=0;i<15;i++)
            item_list[i]=NULL;
    }
    string getName(long id);
    float getRate(long id);
    void print_Updated_ItemList(item*);
};
item* inventory :: item_list[15];
class Manager:public inventory
{
     public:
     using inventory :: Add_item;
     using inventory :: Delete_item;
     using inventory :: Update_item;
     long manager_ID;
     string manager_Name;
     Manager(){};
     Manager(long id,string name)
     {  manager_ID=id; 
        manager_Name=name; 
     };
     
}; 

class Customer
{
    protected:
    void Add_customer(long,string,float);
    void Update_points(long,float); 
    public:
    static customer* customer_list[15];
    void make_CustomerList()
    {
        for(int i=0;i<15;i++)
            customer_list[i]=NULL;
    }
};
customer* Customer :: customer_list[15];
class Billing:public Customer,public inventory
{
    public:
    using Customer :: Add_customer;
    using Customer :: Update_points;
    using inventory :: Change_quantity;
    //string Transaction_ID="ABCDEFGH";
    long Transaction_ID;
    long customer_id=0;
    float total_amount;
    item* item1_list=NULL;
    Billing(){};
    Billing(long id)
    {customer_id=id;
    Transaction_ID=rword(9);
    };
    void buy_item(long,int);
    void cancel_item(long,int);
    void make_payment();
    void print_Updated_CustomerList();
    void print_bill();
};

void inventory :: Add_item(long id,string name,float rate,int qua)
{
    int index=id % 15;
    item* temp= new item;
    temp->item_ID=id;
    temp->Name=name;
    temp->Rate=rate;
    temp->Quantity=qua;
    temp->next=NULL;
    item* current=item_list[index];
    if(current==NULL)
    {   item_list[index]=temp;   }
    else
    {
        while( current->next != NULL )
        {
            current=current->next;
        }
        current->next=temp;
    }
}
void inventory :: Delete_item(long id)
{
    int index=id % 15;
     item* parent = item_list[index];
    if(parent==NULL)
    { cout << "\n There is no product with ID : " << id << endl; }
    else
    {
        item* current=parent->next;
        if(parent->item_ID==id)
        { 
            item_list[index]=current;
            delete parent;
        }
        else
        {
            while( (current!=NULL) && (current->item_ID!=id) )
            {   parent=current;
                current=current->next;}
            if(current==NULL)
            { cout << "\n There is no product with ID : " << id << endl; }
            else
            {
                parent->next=current->next;
                delete current;
            }
        }
    }
}
void inventory :: Update_item(long id, float rate,int qua)
{
    int index=id % 15;
    item * temp=item_list[index];
    while(id!=temp->item_ID)
        temp=temp->next;
    temp->Rate=rate;
    temp->Quantity=qua;
}
int inventory :: Change_quantity(long id,int q)
{
    int index=id % 15;
    item * temp=item_list[index];
    while( (temp!=NULL) && (id!=temp->item_ID) )
        temp=temp->next;
    if(temp==NULL)
    {cout << "\nProduct with Id " << id << " is deleted by Manager. You can't buy this Product."<< endl;
        q=0;return q;}
    while(q>temp->Quantity)
    {
        if(temp->Quantity==0)
        {
            cout << "\n Product with Id " << temp->item_ID << " is out of stock.You can't buy it" << endl;
            q=0;
            return q;
        }
        else
        {   cout << "\n Req. quantity of product " << id << " is more than stock. We have only " << temp->Quantity << " items left in stock." << endl;
        q=temp->Quantity;}
    }
    temp->Quantity=temp->Quantity-q;
    return q;
}
string inventory :: getName(long id)
{
    int index=id % 15;
    item * temp=item_list[index];
    while( (temp!=NULL) && (id!=temp->item_ID) )
        temp=temp->next;
    if(temp==NULL)
    {return " ";}
    return temp->Name;
}
float inventory :: getRate(long id)
{
    int index=id % 15;
    item * temp=item_list[index];
    while( (temp!=NULL) && (id!=temp->item_ID) )
        temp=temp->next;
    if(temp==NULL)
    {return 0;}
    return temp->Rate;
}
void inventory :: print_Updated_ItemList(item * temp)
{   int index;
    item* temp1;
    cout << "\nThe Updated item list is..." << endl;
    cout << " Product ID,    Name,        Rate,    Quantity" << endl;  
    while(temp!=NULL)
    {   
        index=temp->item_ID % 15;
        temp1=item_list[index];
        while( (temp1!=NULL) && (temp->item_ID != temp1->item_ID) )
        {temp1=temp1->next;}
        if(temp1==NULL)
        {cout << "Product with id " << temp->item_ID << " is deleted from stock." << endl;}
         else{cout << temp1->item_ID << ",  " << temp1->Name << ",   " << temp1->Rate << ",     " << temp1->Quantity <<endl;}
        temp=temp->next;
    }
}
void Customer :: Add_customer(long id,string name,float n)
{
    int index=id % 15;
    customer* temp= new customer;
    temp->customer_ID=id;
    temp->Name=name;
    temp->Points=n;
    temp->next=NULL;
    customer* current=customer_list[index];
    if(current==NULL)
    {   customer_list[index]=temp;   }
    else
    {
        while( current->next != NULL )
        {
            current=current->next;
        }
        current->next=temp;
    }
}
void Customer :: Update_points(long id,float n)
{
    int index=id % 15;
    customer* temp=customer_list[index];
    while(id!=temp->customer_ID)
        temp=temp->next;
    temp->Points=temp->Points+n;
}

void Billing :: buy_item(long id, int q=1)
{
    item* temp=new item;
    temp->item_ID=id;
    temp->Name=getName(id);
    temp->Rate=getRate(id);
    q=Change_quantity(id,q);
    temp->Quantity=q;
    temp->Amount= temp->Rate * q;
    temp->next=NULL;
    item* current=item1_list;
    if(current==NULL)
    {   item1_list=temp;   }
    else
    {
        while( current->next != NULL )
        {
            current=current->next;
        }
        current->next=temp;
    }
}
void Billing :: cancel_item(long id,int q=0)
{
    item* parent = item1_list;
    if(parent==NULL)
    { cout << "\nThere is no product in shoping-list with ID : " << id << endl; }
    else
    {
        item* current=parent->next;
        if(parent->item_ID==id)
        {   
            if(q==0)
            {   Change_quantity(id,-(parent->Quantity));
                parent->Quantity=0;
            }
            else{
                Change_quantity(id,-q);
                parent->Quantity = parent->Quantity-q;
                parent->Amount = parent->Quantity * parent->Rate;
            }
        }
        else
        {
            while( (current!=NULL) && (current->item_ID!=id) )
            {   parent=current;
                current=current->next;}
            if(current==NULL)
            { cout << "\nThere is no product in shoping-list with ID : " << id << endl; }
            else
            {
                if(q==0)
                {   Change_quantity(id,-(current->Quantity));
                    current->Quantity=0;
                }
                else{
                    Change_quantity(id,-q);
                    current->Quantity = current->Quantity-q;
                    current->Amount = current->Quantity * current->Rate;
                }
            }
        }
    }
}
void Billing :: print_bill()
{
    item* temp=item1_list;
    total_amount=0;
    cout << "\nTransaction_ID : " << Transaction_ID << endl;
    cout << "Customer_ID : " << customer_id << endl;
    cout << " Product ID,    Name,        Rate,  Quantity,  Amount" << endl; 
    while(temp!=NULL)
    {   if(temp->Quantity!=0)
        {total_amount+=temp->Amount;
        cout << temp->item_ID << ",  " << temp->Name << ",   " << temp->Rate << ",     " << temp->Quantity << ",       " << temp->Amount<< endl;}
        temp=temp->next;
    }
    Update_points(customer_id,total_amount);
    cout << "Total amount : Rs." << total_amount << endl;
}
void Billing :: print_Updated_CustomerList()
{
    int index=customer_id % 15;
    customer* temp=customer_list[index];
    cout << "\nThe Updated customer list is..." << endl;
    while(customer_id!=temp->customer_ID)
    {temp=temp->next;}
    cout << temp->customer_ID << ",  " << temp->Name << ",   " << temp->Points << endl;
}
void Billing :: make_payment()
{
    if(customer_id!=0)
    {
        if(item1_list!=NULL)
        {   
            int index=customer_id % 15;
            customer* temp1=customer_list[index];
            while( (temp1!=NULL) && (customer_id != temp1->customer_ID) )
            {
                temp1=temp1->next;
            }
            if(temp1==NULL)
            {
                cout << "\n You are new customer. Please enter your name : ";
                string name;
                cin >> name;
                Add_customer(customer_id,name,0);
            }
            print_bill();
            print_Updated_ItemList(item1_list);
            print_Updated_CustomerList();
        }
    }
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    // initializing INVENTORY_DATASET...
    dataset1 INVENTORY_DATASET[100] = {
    {111100000001,"product_1",100,20},{111100000002,"product_2",110,20},{111100000003,"product_3",120,20},{111100000004,"product_4",130,20},{111100000005,"product_5",140,20},{111100000006,"product_6",150,20},{111100000007,"product_7",160,20},{111100000008,"product_8",170,20},{111100000009,"product_9",180,20},{111100000010,"product_10",190,20},
    {111100000011,"product_11",200,20},{111100000012,"product_12",210,20},{111100000013,"product_13",220,20},{111100000014,"product_14",230,20},{111100000015,"product_15",240,20},{111100000016,"product_16",250,20},{111100000017,"product_17",260,20},{111100000018,"product_18",270,20},{111100000019,"product_19",280,20},{111100000020,"product_20",290,20},
    {111100000021,"product_21",300,20},{111100000022,"product_22",310,20},{111100000023,"product_23",320,20},{111100000024,"product_24",330,20},{111100000025,"product_25",340,20},{111100000026,"product_26",350,20},{111100000027,"product_27",360,20},{111100000028,"product_28",370,20},{111100000029,"product_29",380,20},{111100000030,"product_30",390,20},
    {111100000031,"product_31",400,20},{111100000032,"product_32",410,20},{111100000033,"product_33",420,20},{111100000034,"product_34",430,20},{111100000035,"product_35",440,20},{111100000036,"product_36",450,20},{111100000037,"product_37",460,20},{111100000038,"product_38",470,20},{111100000039,"product_39",480,20},{111100000040,"product_40",490,20},
    {111100000041,"product_41",500,20},{111100000042,"product_42",510,20},{111100000043,"product_43",520,20},{111100000044,"product_44",530,20},{111100000045,"product_45",540,20},{111100000046,"product_46",550,20},{111100000047,"product_47",560,20},{111100000048,"product_48",570,20},{111100000049,"product_49",580,20},{222200001111,"product_50",590,20},
    {222200001114,"product_51",600,20},{222200001117,"product_52",610,20},{222200001120,"product_53",620,20},{222200001123,"product_54",630,20},{222200001126,"product_55",640,20},{222200001129,"product_56",650,20},{222200001132,"product_57",660,20},{222200001135,"product_58",670,20},{222200001138,"product_59",680,20},{222200001141,"product_60",690,20},
    {222200001144,"product_61",700,20},{222200001147,"product_62",710,20},{222200001150,"product_63",720,20},{222200001153,"product_64",730,20},{222200001156,"product_65",740,20},{222200001159,"product_66",750,20},{222200001162,"product_67",760,20},{222200001165,"product_68",770,20},{222200001168,"product_69",780,20},{222200001171,"product_70",790,20},
    {222200001174,"product_71",800,20},{222200001177,"product_72",810,20},{222200001180,"product_73",820,20},{222200001183,"product_74",830,20},{222200001186,"product_75",840,20},{222200001189,"product_76",850,20},{222200001192,"product_77",860,20},{222200001195,"product_78",870,20},{222200001198,"product_79",880,20},{222200001201,"product_80",890,20},
    {222200001204,"product_81",900,20},{222200001207,"product_82",910,20},{222200001210,"product_83",920,20},{222200001213,"product_84",930,20},{222200001216,"product_85",940,20},{222200001219,"product_86",950,20},{222200001222,"product_87",960,20},{222200001225,"product_88",970,20},{222200001228,"product_89",980,20},{222200001231,"product_90",990,20},
    {222200001234,"product_91",1000,20},{222200001237,"product_92",1010,20},{222200001240,"product_93",1020,20},{222200001243,"product_94",1030,20},{222200001246,"product_95",1040,20},{222200001249,"product_96",1050,20},{222200001252,"product_97",1060,20},{222200001255,"product_98",1070,20},{222200001258,"product_99",1080,20},{222200001261,"product_100",1090,20}
};
    // Initializing CUSTOMER_DATASET...
        dataset2 CUSTOMER_DATASET[100] = {
    {9400000001,"customer_1",0},{9400000002,"customer_2",0},{9400000003,"customer_3",0},{9400000004,"customer_4",0},{9400000005,"customer_5",0},{9400000006,"customer_6",0},{9400000007,"customer_7",0},{9400000008,"customer_8",0},{9400000009,"customer_9",0},{9400000010,"customer_10",0},
    {9400000011,"customer_11",0},{9400000012,"customer_12",0},{9400000013,"customer_13",0},{9400000014,"customer_14",0},{9400000015,"customer_15",0},{9400000016,"customer_16",0},{9400000017,"customer_17",0},{9400000018,"customer_18",0},{9400000019,"customer_19",0},{9400000020,"customer_20",0},
    {9400000021,"customer_21",0},{9400000022,"customer_22",0},{9400000023,"customer_23",0},{9400000024,"customer_24",0},{9400000025,"customer_25",0},{9400000026,"customer_26",0},{9400000027,"customer_27",0},{9400000028,"customer_28",0},{9400000029,"customer_29",0},{9400000030,"customer_30",0},
    {9400000031,"customer_31",0},{9400000032,"customer_32",0},{9400000033,"customer_33",0},{9400000034,"customer_34",0},{9400000035,"customer_35",0},{9400000036,"customer_36",0},{9400000037,"customer_37",0},{9400000038,"customer_38",0},{9400000039,"customer_39",0},{9400000040,"customer_40",0},
    {9400000041,"customer_41",0},{9400000042,"customer_42",0},{9400000043,"customer_43",0},{9400000044,"customer_44",0},{9400000045,"customer_45",0},{9400000046,"customer_46",0},{9400000047,"customer_47",0},{9400000048,"customer_48",0},{9400000049,"customer_49",0},{9400000050,"customer_50",0},
    {9400000051,"customer_51",0},{9400000052,"customer_52",0},{9400000053,"customer_53",0},{9400000054,"customer_54",0},{9400000055,"customer_55",0},{9400000056,"customer_56",0},{9400000057,"customer_57",0},{9400000058,"customer_58",0},{9400000059,"customer_59",0},{9400000060,"customer_60",0},
    {9400000061,"customer_61",0},{9400000062,"customer_62",0},{9400000063,"customer_63",0},{9400000064,"customer_64",0},{9400000065,"customer_65",0},{9400000066,"customer_66",0},{9400000067,"customer_67",0},{9400000068,"customer_68",0},{9400000069,"customer_69",0},{9400000070,"customer_70",0},
    {9400000071,"customer_71",0},{9400000072,"customer_72",0},{9400000073,"customer_73",0},{9400000074,"customer_74",0},{9400000075,"customer_75",0},{9400000076,"customer_76",0},{9400000077,"customer_77",0},{9400000078,"customer_78",0},{9400000079,"customer_79",0},{9400000080,"customer_80",0},
    {9400000081,"customer_81",0},{9400000082,"customer_82",0},{9400000083,"customer_83",0},{9400000084,"customer_84",0},{9400000085,"customer_85",0},{9400000086,"customer_86",0},{9400000087,"customer_87",0},{9400000088,"customer_88",0},{9400000089,"customer_89",0},{9400000090,"customer_90",0},
    {9400000091,"customer_91",0},{9400000092,"customer_92",0},{9400000093,"customer_93",0},{9400000094,"customer_94",0},{9400000095,"customer_95",0},{9400000096,"customer_96",0},{9400000097,"customer_97",0},{9400000098,"customer_98",0},{9400000099,"customer_99",0},{9400000100,"customer_100",0}
    };
    
    // Making manager object (using ID and Name) using paramatrised constructor. 
    Manager m(123456789,"Jinesh");
    m.make_ItemList();          // Initializing item_list array with NULL.
    for(int i=0;i<100;i++)      // Adding 100 items from INVENTORY_DATASET to item_list[15];
    {
    m.Add_item(INVENTORY_DATASET[i].id,INVENTORY_DATASET[i].name,INVENTORY_DATASET[i].rate,INVENTORY_DATASET[i].qq);
    }

    Billing b;                       // Making Billing object to add customers. 
    b.make_CustomerList();           // Initializing customer_list array with NULL.
    for(int i=0;i<100;i++)           // Adding 100 customers from CUSTOMER_DATASET to customer_list[15];
    {
    b.Add_customer(CUSTOMER_DATASET[i].id,CUSTOMER_DATASET[i].name,CUSTOMER_DATASET[i].points);
    }

    
    /* 
        Once the make_payment() function is called, you can not add or cancle item from the same object of Billing(even
        for the same customer). Always make a new object of Billing after make_payment() fun. is called.
        
        buy_item(id,quantity) : if we use buy_item(id) , default quantity is 1.
                                 else add 'quantity' items of product with ID='id' in shopping-list.
        cancel_item(id,quantity) : if we use cancel_item(id) , remove all the items of product with ID='id'.
                                    else remove 'quantity' items of product with ID='id' from shopping-list.
                                    
        In make_payment() fun. print_Updated_ItemList() function print will print all the things which are used
        in the buy_item() or cancel_item() functions.
                                    
    */
    // Following example will contain all the functionalities of supermarket.
    
    Billing b1(9400000052);
    b1.buy_item(111100000022,7);
    b1.buy_item(111100000023,20);
    b1.cancel_item(111100000022,1);         // Remove 1 item of given product out of 3.
    b1.buy_item(222200001225,2);
    b1.buy_item(222200001261,3);
    b1.make_payment();
    
    m.Delete_item(222200001225);            // Delete the given product of item_list from supermarket.
    m.Update_item(222200001261,222,22);     // Update the Rate & Quantity of given produt.
    
    Billing b2(9400000001);
    b2.buy_item(222200001261,5);
    b2.buy_item(111100000022,4);
    b2.buy_item(222200001192,15);
    b2.buy_item(222200001225,10);
    b2.buy_item(222200001162);              // buy 1 item of given product.
    b2.cancel_item(222200001162);          // Remove all the items of given product
    b2.make_payment();    
    
    Billing b3(9400000001);
    b3.buy_item(111100000023,5);            // If given product is out of stock; customer would not get anything.
    b3.buy_item(111100000022,12);           // If customer req. more items than in stock, he should be given all the remaining stock from the supermarket.
    b3.buy_item(222200001225,1);
    b3.buy_item(222200001162,3);
    b3.make_payment();

    return 0;
    
    
}
