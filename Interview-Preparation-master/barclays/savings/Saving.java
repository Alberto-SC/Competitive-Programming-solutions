package com.interview.barclays.savings;

public class Saving {
	private SavingsType savingsType;
	
	private double investment;
	
	public Saving(){
		
	}
	
	public Saving(SavingsType savingsType, double investment){
		this.savingsType = savingsType;
		this.investment = investment;
	}

	public SavingsType getSavingsType() {
		return savingsType;
	}

	public void setSavingsType(SavingsType savingsType) {
		this.savingsType = savingsType;
	}

	public double getInvestment() {
		return investment;
	}

	public void setInvestment(double investment) {
		this.investment = investment;
	}

}
