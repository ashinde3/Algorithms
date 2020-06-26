#include <string>
#include <string.h>
#include <vector>
#include <cstring>
#include <list>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <cfloat>
#include <limits>
#include <queue>
#include <ctime>
#include <chrono>

using namespace std;

//Define structure for card and its market prices
struct card
{
  string playerName;
  int marketPrice;
  int listPrice = -1;
};

//Define structure for user's budget to purchase cards
struct problem
{
  int number;
  int bud;
  vector<card> cards;
};

//Define structure for number of cards bought and max profit computed
struct solution
{
  int numcards2;
  int profit2;
  int numcardspurchased;
  float time;
};

solution computeMaxProfit(problem p);

int main(int argc, char** argv)
{
  int numcards = 0;
  ifstream marketfile;
  ifstream pricefile;
  string m = "-m";
  string p = "-p";
  vector<card> cards_avail;
  for(int i = 0 ; i < argc ; i++)
  {
    string arg = argv[i];
    if(m.compare(arg)==0)
    {
      marketfile.open(argv[i+1]); //Read and open market price file
    }
    if(p.compare(arg)==0)
    {
      pricefile.open(argv[i+1]); //Read and open price list file
    }
  }
  if(!marketfile.is_open())
  {
		cout << "market file could not be opened" << endl;
	}
  vector<problem> problems;
  while(marketfile >> numcards){
    for(int i = 0 ; i < numcards ; i++)
    {
      card baseballcard;
      string name;
      int mprice;
      marketfile >> name;
      marketfile >> mprice;
      baseballcard.playerName = name;
      baseballcard.marketPrice = mprice;
      cards_avail.push_back(baseballcard);
    }
  }
  marketfile.clear();
  marketfile.close();  //Close market price file
  if(!pricefile.is_open())
  {
		cout << "price file could not be opened" << endl;
  }
  int cardselling;
  int budget;
  string playerpricename;
  int playerprice;
  while(pricefile >> cardselling >> budget)
  {
    problem p;
    p.number = cardselling;
    //cout << "cardselling : " << cardselling << endl;
    p.bud = budget;
    //cout << "budget : " << budget << endl;
    for(int i = 0 ; i < cardselling ; i++)
    {
      pricefile >> playerpricename;
      //cout << "player price name : " << playerpricename << endl;
      pricefile >> playerprice;
      //cout << "player price : " << playerprice << endl;
      for(int j = 0 ; j < cards_avail.size() ; j++)
      {
        if(playerpricename.compare(cards_avail[j].playerName)==0)
        {
          cards_avail[j].listPrice = playerprice;
          p.cards.push_back(cards_avail[j]);
        }
      }
    }
    problems.push_back(p);
  }
  pricefile.close();   //Close price list file
  vector<solution> solutions;
  ofstream output;
  output.open("output.txt"); //To write output to the file
  for(int i = 0 ; i < problems.size() ; i++)
  {
      solution s = computeMaxProfit(problems[i]);
      output <<"Number of cards:"<< s.numcards2<< "\t"<<"Profit:" << s.profit2 << "\t"<<"Cards purchased:" << s.numcardspurchased << "\t"<<"Time:" << s.time << endl;
  }
  output.close(); //Close output file
}

//Compute Max Profit
solution computeMaxProfit(problem p)
{
  std::chrono::time_point<std::chrono::system_clock> s, e;
  s = std::chrono::system_clock::now();
  const clock_t begin_time = clock();

  int maxProfit = 0;
  vector< vector<card> > powerset;
  vector<card> subset1;
  int sumprice = 0;
  int budget = p.bud;
  for(int i = 0 ; i < p.cards.size(); i++)
  {
    sumprice = sumprice + p.cards[i].listPrice;
  }
  vector<card> final;
  if(sumprice < budget || sumprice == budget)
  {
    for(int i = 0 ; i < p.cards.size(); i++)
    {
        subset1.push_back(p.cards[i]);
        maxProfit= maxProfit + p.cards[i].marketPrice - p.cards[i].listPrice;

    }
    powerset.push_back(subset1);
    final = subset1;
  }
  else
  {
    for(int i = 0 ; i < pow(2,p.cards.size()) ; i++)
    {
      vector<card> subset;
      for(int j = 0 ; j < p.cards.size() ; j++)
      {
        if(i & (1 << j)){
          subset.push_back(p.cards[j]);
        }
      }
      powerset.push_back(subset);
    }
    int currsum = 0, currprice = 0;
    for(int i = 0 ; i < powerset.size() ; i++)
    {
      vector<card> curr = powerset[i];
      for(int j = 0 ; j < powerset[i].size() ; j++)
      {
        currsum = currsum + curr[j].marketPrice - curr[j].listPrice;
        currprice = currprice + curr[j].listPrice;
      }
      if(currprice < budget || currprice == budget)
      {
        if(currsum > maxProfit)
        {
          maxProfit=currsum;
          final = curr;
        }
      }
      currsum = 0;
      currprice = 0;
    }
  }
  solution s1;
  s1.numcardspurchased = final.size();
  s1.profit2 = maxProfit;
  s1.numcards2 = p.cards.size();
  e = std::chrono::system_clock::now();
  std::chrono::duration<float> els = e - s;
  s1.time = els.count();


  return s1;
};
