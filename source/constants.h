/* CPU PATHS */

#define CPU_INFO "/proc/cpuinfo"
#define CURRENT_CPU_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq"
#define CURRENT_MAX_CPU_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"
#define CURRENT_MIN_CPU_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq"
#define CURRENT_CPU_GOV "/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
#define SCALING_AVAILABLE_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_frequencies"
#define SCALING_AVAILABLE_GOVS "/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors"

/* GPU PATHS */

#define GPU_UP_THRESHOLD "/sys/module/msm_kgsl_core/parameters/up_threshold"
#define GPU_DOWN_THRESHOLD "/sys/module/msm_kgsl_core/parameters/down_threshold"

#define GPU_AVAILABLE_FREQ "/sys/class/kgsl/kgsl-3d0/gpu_available_frequencies"
#define GPU_MAX_FREQ "/sys/class/kgsl/kgsl-3d0/max_gpuclk"
#define GPU_CURRENT_FREQ "/sys/class/kgsl/kgsl-3d0/gpuclk"

/* BATTERY PATHS */

#define BATTERY_STATUS "/sys/class/power_supply/battery/status"
#define BATTERY_TECHNOLOGY "/sys/class/power_supply/battery/technology"
#define BATTERY_CAPACITY "/sys/class/power_supply/battery/capacity"
#define BATTERY_VOLTAGE "/sys/class/power_supply/battery/voltage_now"
#define BATTERY_DESING_MAX_VOLTAGE "/sys/class/power_supply/battery/voltage_max_design"
#define BATTERY_DESING_MIN_VOLTAGE "/sys/class/power_supply/battery/voltage_min_design"
#define BATTERY_HEALTH "/sys/class/power_supply/battery/health"
#define BATTERY_TEMP "/sys/class/power_supply/battery/temp"
#define BATTERY_TEMP_OLD "/sys/class/power_supply/battery/batt_temp"


/* HOTPLUG PATHS */

#define HOTPLUG_PATH "/sys/devices/virtual/misc/mako_hotplug_control"
#define CPUFREQ_UNPLUG_LIMIT "/sys/devices/virtual/misc/mako_hotplug_control/cpufreq_unplug_limit"
#define HIGH_LOAD_COUNTER "/sys/devices/virtual/misc/mako_hotplug_control/high_load_counter"
#define LOAD_THRESHOULD "/sys/devices/virtual/misc/mako_hotplug_control/load_threshold"
#define MAX_LOAD_COUNTER "/sys/devices/virtual/misc/mako_hotplug_control/max_load_counter"
#define MIN_TIME_CPU_ONLINE "/sys/devices/virtual/misc/mako_hotplug_control/min_time_cpu_online"
#define HOTPLUG_TIMER "/sys/devices/virtual/misc/mako_hotplug_control/timer"

/* EXTRA PATHS */

#define TEMP_THRESHOLD "/sys/module/msm_thermal/parameters/temp_threshold"
#define VIBRATION_AMP "/sys/class/timed_output/vibrator/amp"
#define FORCE_FAST_CHARGE "/sys/kernel/fast_charge/force_fast_charge"
#define AVAILABLE_TCP_CONGESTION_ALGORITHM "/proc/sys/net/ipv4/tcp_available_congestion_control"
#define TCP_CONGESTION_ALGORITHM "/proc/sys/net/ipv4/tcp_congestion_control"

#define SOUND_CONTROL_PATH "sys/class/misc/soundcontrol"
