package com.interview.barclays.savings;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ExemptionsForIndia implements SavingScheme {

	@Override
	public double getExemptions(List<Saving> savings) {
		Map<SavingsGroupsForIndia, Double> exemptions = new HashMap<>();
		double totalExemption = 0.0;
		if(savings != null){
			for(Saving saving : savings){
				SavingsGroupsForIndia savingGroup = getSavingGroup(saving.getSavingsType());
				Double amount = exemptions.get(savingGroup);
				if(amount==null){
					if(saving.getInvestment() > savingGroup.getMaxLimit())
						exemptions.put(savingGroup, savingGroup.getMaxLimit());
					else
						exemptions.put(savingGroup, saving.getInvestment());
				}else{
					amount += saving.getInvestment();
					if(amount > savingGroup.getMaxLimit())
						exemptions.put(savingGroup, savingGroup.getMaxLimit());
					else
						exemptions.put(savingGroup, amount);
				}
			}	
		
			for(Double d : exemptions.values()){
				totalExemption +=d;
			}
		}
		return totalExemption;
	}

	private SavingsGroupsForIndia getSavingGroup(SavingsType savingsType) {
		switch(savingsType){
		case PPF:
		case FD:
		case LIC:
		default:
			return SavingsGroupsForIndia.SECTION_80_C;
		case MEDICLAIM:
		case EDUCATION_LOAN:
		case HOME_LOAN:
			return SavingsGroupsForIndia.SECTION_80_D;
		
		}
	}
	
}
