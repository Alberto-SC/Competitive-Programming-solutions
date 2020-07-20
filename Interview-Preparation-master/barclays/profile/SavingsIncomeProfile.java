package com.interview.barclays.profile;

import java.util.List;

import com.interview.barclays.savings.Saving;

public class SavingsIncomeProfile extends IncomeProfile {
	
	private List<Saving> savings;
	
	public SavingsIncomeProfile(double salary, CountryCode country, List<Saving> savings) {
		super(salary, country);
		this.savings = savings;
	}
	
	public SavingsIncomeProfile(double salary, CountryCode country) {
		super(salary, country);
	}	

	public List<Saving> getSavings() {
		return savings;
	}

	public void setSavings(List<Saving> savings) {
		this.savings = savings;
	}

	@Override
	public double getTaxableIncome() {
		
		double income = super.getTaxableIncome();
		double exemption = super.getCountry().getSavingScheme().getExemptions(savings);
		
		return income - exemption;
	}

	
}
