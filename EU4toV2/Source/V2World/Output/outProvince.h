#ifndef OUT_PROVINCE_H
#define OUT_PROVINCE_H

#include "../Province/Province.h"

namespace V2
{
	std::ostream& operator<<(std::ostream& output, const Province& province);
	std::ostream& operator<<(std::ostream& output, const std::optional<std::pair<int, std::vector<std::shared_ptr<V2::Pop>>>>& pops);

}

#endif // OUT_PROVINCE_H
