#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <map>
#include <set>
#include <thread>
#include <chrono>
#include <cstdint>
#include <array>
#include <stack>
#include <queue>
#include <list>
#include <fstream>
#include <mutex>
#include <iomanip>

#include "PulseStudio/Core.h"
#include "PulseStudio/Log.h"

#include "PulseStudio/KeyCodes.h"
#include "PulseStudio/MouseButtonCodes.h"

#ifdef PS_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
