#include "MinorityPopMapper.h"
#include "MinorityPop.h"
#include "ParserHelpers.h"

mappers::MinorityPopMapper::MinorityPopMapper()
{
	registerKeys();
	parseFile("configurables/minority_pops.txt");
	clearRegisteredKeywords();
}

mappers::MinorityPopMapper::MinorityPopMapper(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void mappers::MinorityPopMapper::registerKeys()
{
	registerKeyword("minority", [this](const std::string& unused, std::istream& theStream)
		{
			const MinorityPop minPop(theStream);
			minorityPopMap.emplace_back(make_pair(minPop.getCulture(), minPop.getReligion()));
		});
	registerRegex("[a-zA-Z0-9\\_.:]+", commonItems::ignoreItem);
}

bool mappers::MinorityPopMapper::blankMajorityFromMinority(V2::Pop& pop) const
{
	// We are blanking majority part from a minority pop so that we may apply any
	// religion to gipsies or any culture to mormons.
	for (const auto& minorityItr : minorityPopMap)
	{
		if (pop.getCulture() == minorityItr.first && pop.getReligion() == minorityItr.second)
		{
			return true;
		}
		if (minorityItr.first.empty() && pop.getReligion() == minorityItr.second)
		{
			pop.setCulture("");
			return true;
		}
		if (pop.getCulture() == minorityItr.first && minorityItr.second.empty())
		{
			pop.setReligion("");
			return true;
		}
	}
	return false;
}
