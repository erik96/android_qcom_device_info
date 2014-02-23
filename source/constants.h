
/* CPU PATHS */

const char *pCPUInfo = "/proc/cpuinfo";
const char *pCurrCPUFeq = "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq";
const char *pCurrMaxCPUFreq = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq";
const char *pCurrMinCPUFreq = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq";
const char *pCurrCPUGov = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor";
const char *pScalingFreq = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_frequencies";
const char *pScalingGovs = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors";


/* GPU PATHS */

const char *GPU_UP_THRESHOLD = "/sys/module/msm_kgsl_core/parameters/up_threshold";
const char *GPU_DOWN_THRESHOLD = "/sys/module/msm_kgsl_core/parameters/down_threshold";

const char *GPU_AVAILABLE_FREQ = "/sys/class/kgsl/kgsl-3d0/gpu_available_frequencies";
const char *GPU_MAX_FREQ = "/sys/class/kgsl/kgsl-3d0/max_gpuclk";
const char *CURR_GPU_FREQ = "/sys/class/kgsl/kgsl-3d0/gpuclk";


/* HOTPLUG PATHS */

const char *CPUFREQ_UNPLUG_LIMIT = "/sys/devices/virtual/misc/mako_hotplug_control/cpufreq_unplug_limit";
const char *HIGH_LOAD_COUNTER = "/sys/devices/virtual/misc/mako_hotplug_control/high_load_counter";
const char *LOAD_THRESHOULD = "/sys/devices/virtual/misc/mako_hotplug_control/load_threshold";
const char *MAX_LOAD_COUNTER = "/sys/devices/virtual/misc/mako_hotplug_control/max_load_counter";
const char *MIN_TIME_CPU_ONLINE = "/sys/devices/virtual/misc/mako_hotplug_control/min_time_cpu_online";
const char *HOTPLUG_TIMER = "/sys/devices/virtual/misc/mako_hotplug_control/timer";

