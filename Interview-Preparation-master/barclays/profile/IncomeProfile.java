package com.interview.barclays.profile;

public class IncomeProfile {
	
	private double taxableIncome;
	
	private CountryCode country;

	public IncomeProfile(double salary, CountryCode country){
		this.taxableIncome = salary;
		this.country = country;
	}
	public double getTaxableIncome() {
		return taxableIncome;
	}

	public void setTaxableIncome(double taxableIncome) {
		this.taxableIncome = taxableIncome;
	}

	public CountryCode getCountry() {
		return country;
	}

	public void setCountry(CountryCode country) {
		this.country = country;
	}
	
	
}
