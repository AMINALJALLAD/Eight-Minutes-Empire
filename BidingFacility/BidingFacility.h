#ifndef BINDINGFACILITY_H
#define BINDINGFACILITY_H

class BidingFacility
{
	public:
		BidingFacility();
		~BidingFacility();
		BidingFacility(int coins_);
		int getBid();
		void show();
	private:
		void getBidByUser(int coin_);
		bool isValidBid(int coin_);
		int* bidCoin;
};
#endif

