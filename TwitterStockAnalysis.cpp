
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {

    return 0;
}
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <class T>
class Data
{
    public:
        T key;
        T value;
        int sentiment;
        
        Data()
        {
            //key = "";
            //value = "";
        };
        Data(T k, T v, int senti)
        {
            key = k;
            value = v;
            sentiment = senti;
        };
};

template <class T>
class Element
{
    public:
        Data<T> d;
        Element* prev;
        Element* next;
        
        Element()
        {
            //d.key = "";
            //d.value = "";
            prev = NULL;
            next = NULL;
        };
        Element(Data<T> dat)
        {
            d = dat;
            prev = NULL;
            next = NULL;
        };
};
template <class T>
class DataSlot
{
    public:
        T index;
        long size,positive,negative,neutral;        
        
        DataSlot()
        {
            //index = "";
            size = 0;
            positive = 0;
            negative = 0;
            neutral = 0;
        };
        DataSlot(T s)
        {
            index = s;
            size = 0;
            positive = 0;
            negative = 0;
            neutral = 0;
        };
};

template <class T>
class Slot
{
    public:
        DataSlot<T> ds;
        Slot* prev;
        Slot* next;
        Element<T>* head;
        
        class ElementAlreadyPresentInSlot
        {};
        class SlotEmpty
        {};
        class ElementNotPresentInSlot
        {};
        
        Slot()
        {
            //ds.index = "";
            ds.size = 0;
            prev = NULL;
            next = NULL;
            head = NULL;
        };
        Slot(DataSlot<T> datS)
        {
            ds = datS;
            prev = NULL;
            next = NULL;
            head = NULL;
        };
        
        void insert(Element<T>* x)
        {
            
            if (ds.size == 0)
            {
                head = x;
                ds.size++;
                if(x->d.sentiment == 1)
                    ds.positive++;
                else if (x->d.sentiment == -1)
                    ds.negative++;
                else
                    ds.neutral++;
            }
            else
            {
                Element<T>* tempElement = head;
                
                while (tempElement != NULL)
                {
                    if (tempElement == x)
                    {
                        throw ElementAlreadyPresentInSlot();
                        //cout << endl << "Element already present in the given Slot";
                        //break;
                    }
                    else
                    {
                        if (tempElement->next == NULL)
                        {
                            tempElement->next = x;
                            x->prev = tempElement;
                            x->next = NULL;
                            ds.size++;
                            if(x->d.sentiment == 1)
                                ds.positive++;
                            else if (x->d.sentiment == -1)
                                ds.negative++;
                            else
                                ds.neutral++;
                            break;
                        }
                        tempElement = tempElement->next;
                    }
                }
            }
        }
        void delet(Element<T>* x)
        {
            if(ds.size == 0)
            {
                throw SlotEmpty();
                //cout << endl << "Slot already empty";
            }
            else
            {
                Element<T>* tempElement = head;
                int flag = 0;
                
                while (tempElement != NULL)
                {
                    if(tempElement == x)
                    {
                        flag = 1;
                        Element<T>* prevElement = x->prev;
                        Element<T>* nextElement = x->next;
                        
                        if (prevElement != NULL)
                        {
                            prevElement->next = nextElement;
                        }
                        if (nextElement != NULL)
                        {
                            nextElement->prev = prevElement;
                        }
                        if (x == head)
                        {
                            head = NULL;
                        }
                        ds.size--;
                        if(x->d.sentiment == 1)
                            ds.positive--;
                        else if (x->d.sentiment == -1)
                            ds.negative--;
                        else
                            ds.neutral--;                        
                        break;
                    }
                    tempElement = tempElement->next;
                }
                
                if (flag == 0)
                {
                    throw ElementNotPresentInSlot();
                    //cout << endl << "Element not present in this Slot";
                }
            }
        };
        
        ~Slot()
        {
            while(head != NULL)
            {
                delet (head);
            }
        };
};

template <class T>
class HashMap
{
    private:
        long num_slots;
        Slot<T>* First_Slot;
    
    public:   
        HashMap()
        {
            num_slots=0;
            First_Slot = NULL;
        };
        
        class SlotAlreadyPresentInHashMap
        {};
        class HashMapAlreadyEmpty
        {};
        class SlotNotPresentInHashMap
        {};
        
        long int getSize()
        {
            return num_slots;
        };
        
        void insert(Slot<T>* s)
        {
            if (num_slots == 0)
            {
                First_Slot = s;
                s->prev = NULL;
                s->next = NULL;
                num_slots++;
            }
            else
            {
                Slot<T>* tempSlot = First_Slot;
                
                while (tempSlot != NULL)
                {
                    if (tempSlot == s)
                    {
                        throw SlotAlreadyPresentInHashMap();
                        //cout << endl << "Slot already present in HashMap";
                        //break;
                    }
                    else
                    {
                        if (tempSlot->next == NULL)
                        {
                            tempSlot->next = s;
                            s->prev = tempSlot;
                            s->next = NULL;
                            num_slots++;
                            break;
                        }
                        tempSlot = tempSlot->next;
                    }
                }                
            }
            
        };
        
        void insert (Slot<T>* s, Element<T>* x)
        {
            s->insert(x);            
        };
        
        void delet (Slot<T>* s)
        {
            if (num_slots == 0)
            {
                throw HashMapAlreadyEmpty();
                //cout << endl << "HashMap already empty";
            }
            else
            {
                Slot<T>* tempSlot = First_Slot;
                int flag = 0;
                
                while (tempSlot != NULL)
                {
                    if(tempSlot == s)
                    {
                        flag = 1;
                        Slot<T>* prevSlot = s->prev;
                        Slot<T>* nextSlot = s->next;
                        
                        if (prevSlot != NULL)
                        {
                            prevSlot->next = nextSlot;
                        }
                        if (nextSlot != NULL)
                        {
                            nextSlot->prev = prevSlot;
                        }
                        if (s == First_Slot)
                        {
                            First_Slot = First_Slot->next;
                        }
                        num_slots--;
                        break;
                    }
                    tempSlot = tempSlot->next;
                }
                
                if (flag == 0)
                {
                    throw SlotNotPresentInHashMap();
                    //cout << endl << "Slot not present in this Hashmap";
                }
            }
        };
        
        void delet (Slot<T>* s, Element<T>* x)
        {
            s->delet(x);
        };
        
        void display()
        {
            Slot<T>* st;
            Element<T>* em;
            st = First_Slot;
            while(st != NULL)
            {
                cout << "Index: " << st->ds.index << ",\tSize: " << st->ds.size << ",\tPositive: " << st->ds.positive << ",\tNegative: " << st->ds.negative << ",\tNeutral: " << st->ds.neutral << endl;
                em = st->head;
                while (em != NULL)
                {
                    cout << "\tKey: " << em->d.key << ",\tValue: " << em->d.value << endl;
                    em = em->next;
                }
                st = st->next;
            }
        };
        
        void displayTable()
        {
            cout << "Sentiment Analysis of Stocks using Tweets:" << endl;
            cout << "\tStock" << "\t\tPositive" << "\t Neutral" << "\tNegative" << endl;
            Slot<T>* st;
            Element<T>* em;
            st = First_Slot;
            while(st != NULL)
            {
                cout << "\t" << st->ds.index << "\t\t" << st->ds.positive << "\t\t" << st->ds.neutral << "\t\t" << st->ds.negative << endl;                
                st = st->next;
            }            
        };
        
        Slot<T>* findSlot(T s)
        {
            cout << "Trying to find slot match for: " << s << endl;
            Slot<T>* st;            
            st = First_Slot;
            if (st == NULL)
            {
                cout << "HashMap empty" << endl;
                return NULL;
            }
            else
            {
                while(st != NULL)
                {
                    cout << "Index: " << st->ds.index << ",\tSize: " << st->ds.size << endl;
                    if (st->ds.index == s)
                    {
                        cout << "Slot Match Found: " << s << endl;
                        return st;
                    }
                    else
                        st = st->next;
                }
                cout << "No Slot Match Found" << endl;
                return NULL;
            }
        };
    
        ~HashMap()
        {
            while (First_Slot != NULL)
                delet (First_Slot);
        };
};

class SentimentAnalysis
{
private:
    string positive, negative;
    
public:
    SentimentAnalysis(int a)
    {
        positive = "rose,rise,up,good,best,better,high,higher,buy,buying,bought,value,long,exciting,outperform,undervalued,beat,top,underweight,spike,bulls,bullish,gains,rally,";
        negative = "drop,dropped,down,destroy,low,lower,sell,sold,selling,short,crushed,bad,worse,worst,overweight,decline,bearish,bear,bears,selloff,sell-off,panic,doom,losing,";                
    };
    
    int provideSentiment(string twt)   // 1 for positive, 0 for neutral and -1 for negative sentiment
    {
        //cout << "Positive String: " << positive << endl;
        int sentiment = 0;
        int startindex = 0;
        int endindex = positive.find(',',0);
        while (endindex != std::string::npos)
        {
            string word = positive.substr(startindex,endindex-startindex);
            //cout << "Word: " << word << endl;
            if(twt.find(word) != std::string::npos)
            {
                cout << "Positive: " << word << endl;
                sentiment = 1;
            }
            
            startindex = endindex+1;
            endindex = positive.find(',',startindex);
        }
        
        //cout << "Negative String: " << negative << endl;
        startindex = 0;
        endindex = negative.find(',',0);
        while (endindex != std::string::npos)
        {
            string word = negative.substr(startindex,endindex-startindex);
            //cout << "Word: " << word << endl;
            if(twt.find(word) != std::string::npos)
            {
                cout << "Negative: " << word << endl;
                sentiment = -1;
            }
            
            startindex = endindex+1;
            endindex = negative.find(',',startindex);
        }
        return sentiment;
    };
    
    void addPositiveWord(string posit)
    {
        positive = positive+posit+",";        
    };
    
    void addNegativeWord(string negat)
    {
        negative = negative+negat+",";        
    };
};

int main()
{
    HashMap<string>* hm = new HashMap<string>;
    SentimentAnalysis SA(1);
    
    string tweet;
    ifstream myfile("Tweets.txt");
    if(myfile.is_open())
    {
        while(getline(myfile,tweet))
        {
            cout << tweet << endl;
            int sentiment = SA.provideSentiment(tweet);
            cout << "Sentiment: " << sentiment << endl;
            int pos=tweet.find('$',0);
            
            while (pos != std::string::npos)
            {               
                //cout << "Pos: " << pos << endl;
                int endofstock = tweet.find_first_of(" .,:;<>/?1234567890`~!@#$%^&*()-=_+\"'[]{}|\\",pos+1);                
                //cout << "EndofStock: " << endofstock << endl;
                string stock = tweet.substr(pos,endofstock - pos);
                if (endofstock == std::string::npos)
                    stock = tweet.substr(pos,tweet.length()-pos-1);
                
                cout << "Stock:" << stock << ":Stock" << endl;
                pos=tweet.find('$',pos+1);
                
                if (stock != "$")
                {
                    Data<string> data1(stock,tweet,sentiment);
                    Element<string>* element1 = new Element<string>(data1);

                    Slot<string>* slot1 = hm->findSlot(stock);

                    if (slot1 != NULL)
                    {
                        slot1->insert(element1);
                        cout << "Element inserted in existing slot" << endl;
                    }
                    else
                    {
                        DataSlot<string>  dataslot1(stock);
                        slot1 = new Slot<string>(dataslot1);
                        slot1->insert(element1);
                        hm->insert(slot1);
                        cout << "New slot inserted" << endl;
                    }
                }                    
            }
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
    
    hm->display();
    hm->displayTable();    
   
    delete hm;

    return 0;
}


