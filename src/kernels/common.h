#ifndef _COMMON_
#define _COMMON_

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <CL/sycl.hpp>

using namespace cl::sycl;

constexpr access::mode sycl_read               = access::mode::read;
constexpr access::mode sycl_write              = access::mode::write;
constexpr access::mode sycl_read_write         = access::mode::read_write;
constexpr access::mode sycl_discard_read_write = access::mode::discard_read_write;
constexpr access::mode sycl_discard_write      = access::mode::discard_write;

// CUDA device selector
class CUDASelector : public device_selector {
    public:
        int operator()(const device &Device) const override {
            const std::string DriverVersion = Device.get_info<info::device::driver_version>();

            if (Device.is_gpu() && (DriverVersion.find("CUDA") != std::string::npos))
                //std::cout << " CUDA device found " << std::endl;
                return 1;

            return -1;
        }
};

// Intel iGPU
class NEOGPUDeviceSelector : public device_selector {
    public:
        int operator()(const device &Device) const override {
            const std::string DeviceName = Device.get_info<info::device::name>();
            //const std::string DeviceVendor = Device.get_info<info::device::vendor>();
            return Device.is_gpu() && (DeviceName.find("HD Graphics NEO") != std::string::npos);
        }
};

//#define RANDOM
#define DEBUG
const bool verbose = false;
const char PAD = 32;

#if REAL <=4
	#define real float
	#define rmax(a,b) ( ( (a) > (b) )? (a) : (b) )
	#define rsqrt sqrtf
#else
	#define real double
	#define rmax fmax
	#define rsqrt sqrt
#endif

/* Number of iterations before testing convergence (can be adjusted) */
const int NITER_TEST_CONV = 10;

/* Spacing of floating point numbers. */
const real eps = 2.2204e-16;

void adjust_WH(queue &q, buffer<real, 1> &b_W, buffer<real, 1> &b_Ht, int N, int M, int K);
void V_div_WH(queue &q, buffer<real, 1> &b_V, buffer<real, 1> &b_WH, int N, int M);
void mult_M_div_vect(queue &q, buffer<real, 1> &b_M, buffer<real, 1> &b_Maux, buffer<real, 1> &b_acc, int M, int K);

#endif