#pragma once

namespace photon::utils
{
	constexpr bool debug_log = true;

	template <typename... Args>
	static inline void debug_print( Args... args )
	{
		if constexpr ( !debug_log )
			return;

		__android_log_print( ANDROID_LOG_DEBUG, "[DEBUG] photon -- ", args... );
	}

	template <typename... Args>
	static inline void print( Args... args )
	{
		__android_log_print( ANDROID_LOG_INFO, "photon -- ", args... );
	}
}
