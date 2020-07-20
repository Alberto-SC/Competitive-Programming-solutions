package com.interview.barclays.tax.tester;

import java.util.ArrayList;
import java.util.List;

import com.interview.barclays.profile.CountryCode;
import com.interview.barclays.profile.SavingsIncomeProfile;
import com.interview.barclays.savings.Saving;
import com.interview.barclays.savings.SavingsType;

public class SavingsIncomeTaxCalculator {

	public static void main(String[] args) {
		
		testToCalculateNoSavingTaxForIndia();
		
		testToCalculateNoSavingTaxForUSA();
		
		testToCalculateSavingTaxForIndia();
		
		testToCalculateSavingTaxForUSA();

	}
	
	public static void testToCalculateSavingTaxForIndia(){
		List<Saving> savings = new ArrayList<>();
		Saving saving1 = new Saving(SavingsType.FD, 100000);
		Saving saving2 = new Saving(SavingsType.MEDICLAIM, 129500);
		savings.add(saving1);
		savings.add(saving2);
		SavingsIncomeProfile profile1 = new SavingsIncomeProfile(1500000, CountryCode.INDIA, savings);
		double tax = profile1.getCountry().getCalculator().calculateTax(profile1);
		System.out.println(tax);
	}
	
	public static void testToCalculateSavingTaxForUSA(){
		List<Saving> savings = new ArrayList<>();
		Saving saving1 = new Saving(SavingsType.FD, 10000);
		Saving saving2 = new Saving(SavingsType.MEDICLAIM, 1295);
		savings.add(saving1);
		savings.add(saving2);
		SavingsIncomeProfile profile1 = new SavingsIncomeProfile(1500000, CountryCode.USA, savings);
		double tax = profile1.getCountry().getCalculator().calculateTax(profile1);
		System.out.println(tax);
	}

	
	public static void testToCalculateNoSavingTaxForIndia(){
		SavingsIncomeProfile profile1 = new SavingsIncomeProfile(1500000, CountryCode.INDIA);
		double tax = profile1.getCountry().getCalculator().calculateTax(profile1);
		System.out.println(tax);
	}
	
	public static void testToCalculateNoSavingTaxForUSA(){
		SavingsIncomeProfile profile1 = new SavingsIncomeProfile(1500000, CountryCode.USA);
		double tax = profile1.getCountry().getCalculator().calculateTax(profile1);
		System.out.println(tax);
	}
}
