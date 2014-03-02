
/* CPU PATHS */

const char *CPU_INFO = "/proc/cpuinfo";
const char *CURRENT_CPU_FREQ = "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq";
const char *CURRENT_MAX_CPU_FREQ = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq";
const char *CURRENT_MIN_CPU_FREQ = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq";
const char *CURRENT_CPU_GOV = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor";
const char *SCALING_AVAILABLE_FREQ = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_frequencies";
const char *SCALING_AVAILABLE_GOVS = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors";


/* GPU PATHS */

const char *GPU_UP_THRESHOLD = "/sys/module/msm_kgsl_core/parameters/up_threshold";
const char *GPU_DOWN_THRESHOLD = "/sys/module/msm_kgsl_core/parameters/down_threshold";

const char *GPU_AVAILABLE_FREQ = "/sys/class/kgsl/kgsl-3d0/gpu_available_frequencies";
const char *GPU_MAX_FREQ = "/sys/class/kgsl/kgsl-3d0/max_gpuclk";
const char *GPU_CURRENT_FREQ = "/sys/class/kgsl/kgsl-3d0/gpuclk";

/* BATTERY PATHS */

const char *BATTERY_STATUS = "/sys/class/power_supply/battery/status";
const char *BATTERY_TECHNOLOGY = "/sys/class/power_supply/battery/technology";
const char *BATTERY_CAPACITY = "/sys/class/power_supply/battery/capacity";
const char *BATTERY_VOLTAGE = "/sys/class/power_supply/battery/voltage_now";
const char *BATTERY_DESING_MAX_VOLTAGE = "/sys/class/power_supply/battery/voltage_max_design";
const char *BATTERY_DESING_MIN_VOLTAGE = "/sys/class/power_supply/battery/voltage_min_design";
const char *BATTERY_HEALTH = "/sys/class/power_supply/battery/health";
const char *BATTERY_TEMP = "/sys/class/power_supply/battery/temp";
const char *BATTERY_TEMP_OLD = "/sys/class/power_supply/battery/batt_temp";


/* HOTPLUG PATHS */

const char *HOTPLUG_PATH = "/sys/devices/virtual/misc/mako_hotplug_control";
const char *CPUFREQ_UNPLUG_LIMIT = "/sys/devices/virtual/misc/mako_hotplug_control/cpufreq_unplug_limit";
const char *HIGH_LOAD_COUNTER = "/sys/devices/virtual/misc/mako_hotplug_control/high_load_counter";
const char *LOAD_THRESHOULD = "/sys/devices/virtual/misc/mako_hotplug_control/load_threshold";
const char *MAX_LOAD_COUNTER = "/sys/devices/virtual/misc/mako_hotplug_control/max_load_counter";
const char *MIN_TIME_CPU_ONLINE = "/sys/devices/virtual/misc/mako_hotplug_control/min_time_cpu_online";
const char *HOTPLUG_TIMER = "/sys/devices/virtual/misc/mako_hotplug_control/timer";

/* EXTRA PATHS */

//TODO: /sys/class/misc/soundcontrol/

const char *TEMP_THRESHOLD = "/sys/module/msm_thermal/parameters/temp_threshold";
const char *VIBRATION_AMP = "/sys/class/timed_output/vibrator/amp";
const char *FORCE_FAST_CHARGE = "/sys/kernel/fast_charge/force_fast_charge";
const char *AVAILABLE_TCP_CONGESTION_ALGORITHM = "/proc/sys/net/ipv4/tcp_available_congestion_control";
const char *TCP_CONGESTION_ALGORITHM = "/proc/sys/net/ipv4/tcp_congestion_control";



