#include <cmath>

#include <test/test.h>

constexpr float  f32_inf = std::numeric_limits<float> ::infinity();
constexpr double f64_inf = std::numeric_limits<double>::infinity();
constexpr float  f32_nan = std::numeric_limits<float> ::quiet_NaN();
constexpr double f64_nan = std::numeric_limits<double>::quiet_NaN();

TEST_CASE("builtin.math.basic")
{
    ScopedContext ctx;
    
    auto abs32 = to_callable<float>(
        [](f32 x) { $return(math::abs(x)); });
    auto abs64 = to_callable<double>(
        [](f64 x) { $return(math::abs(x)); });
    
    auto mod32 = to_callable<float>(
        [](f32 x, f32 y) { $return(math::mod(x, y)); });
    auto mod64 = to_callable<double>(
        [](f64 x, f64 y) { $return(math::mod(x, y)); });
    
    auto remainder32 = to_callable<float>(
        [](f32 x, f32 y) { $return(math::remainder(x, y)); });
    auto remainder64 = to_callable<double>(
        [](f64 x, f64 y) { $return(math::remainder(x, y)); });
    
    auto exp32 = to_callable<float>(
        [](f32 x) { $return(math::exp(x)); });
    auto exp64 = to_callable<double>(
        [](f64 x) { $return(math::exp(x)); });
    
    auto exp2_32 = to_callable<float>(
        [](f32 x) { $return(math::exp2(x)); });
    auto exp2_64 = to_callable<double>(
        [](f64 x) { $return(math::exp2(x)); });
    
    auto log32 = to_callable<float>(
        [](f32 x) { $return(math::log(x)); });
    auto log64 = to_callable<double>(
        [](f64 x) { $return(math::log(x)); });
    
    auto log2_32 = to_callable<float>(
        [](f32 x) { $return(math::log2(x)); });
    auto log2_64 = to_callable<double>(
        [](f64 x) { $return(math::log2(x)); });
    
    auto log10_32 = to_callable<float>(
        [](f32 x) { $return(math::log10(x)); });
    auto log10_64 = to_callable<double>(
        [](f64 x) { $return(math::log10(x)); });
    
    auto pow32 = to_callable<float>(
        [](f32 x, f32 y) { $return(math::pow(x, y)); });
    auto pow64 = to_callable<double>(
        [](f64 x, f64 y) { $return(math::pow(x, y)); });
    
    auto sqrt32 = to_callable<float>(
        [](f32 x) { $return(math::sqrt(x)); });
    auto sqrt64 = to_callable<double>(
        [](f64 x) { $return(math::sqrt(x)); });
    
    auto sin32 = to_callable<float>(
        [](f32 x) { $return(math::sin(x)); });
    auto sin64 = to_callable<double>(
        [](f64 x) { $return(math::sin(x)); });
    
    auto cos32 = to_callable<float>(
        [](f32 x) { $return(math::cos(x)); });
    auto cos64 = to_callable<double>(
        [](f64 x) { $return(math::cos(x)); });
    
    auto tan32 = to_callable<float>(
        [](f32 x) { $return(math::tan(x)); });
    auto tan64 = to_callable<double>(
        [](f64 x) { $return(math::tan(x)); });
    
    auto asin32 = to_callable<float>(
        [](f32 x) { $return(math::asin(x)); });
    auto asin64 = to_callable<double>(
        [](f64 x) { $return(math::asin(x)); });
    
    auto acos32 = to_callable<float>(
        [](f32 x) { $return(math::acos(x)); });
    auto acos64 = to_callable<double>(
        [](f64 x) { $return(math::acos(x)); });
    
    auto atan32 = to_callable<float>(
        [](f32 x) { $return(math::atan(x)); });
    auto atan64 = to_callable<double>(
        [](f64 x) { $return(math::atan(x)); });
    
    auto atan2_32 = to_callable<float>(
        [](f32 y, f32 x) { $return(math::atan2(y, x)); });
    auto atan2_64 = to_callable<double>(
        [](f64 y, f64 x) { $return(math::atan2(y, x)); });
    
    auto ceil32 = to_callable<float>(
        [](f32 x) { $return(math::ceil(x)); });
    auto ceil64 = to_callable<double>(
        [](f64 x) { $return(math::ceil(x)); });
    
    auto floor32 = to_callable<float>(
        [](f32 x) { $return(math::floor(x)); });
    auto floor64 = to_callable<double>(
        [](f64 x) { $return(math::floor(x)); });
    
    auto trunc32 = to_callable<float>(
        [](f32 x) { $return(math::trunc(x)); });
    auto trunc64 = to_callable<double>(
        [](f64 x) { $return(math::trunc(x)); });
    
    auto round32 = to_callable<float>(
        [](f32 x) { $return(math::round(x)); });
    auto round64 = to_callable<double>(
        [](f64 x) { $return(math::round(x)); });
    
    auto isfinite32 = to_callable<int>(
        [](f32 x) { $return(math::isfinite(x)); });
    auto isfinite64 = to_callable<int>(
        [](f64 x) { $return(math::isfinite(x)); });
    
    auto isinf32 = to_callable<int>(
        [](f32 x) { $return(math::isinf(x)); });
    auto isinf64 = to_callable<int>(
        [](f64 x) { $return(math::isinf(x)); });
    
    auto isnan32 = to_callable<int>(
        [](f32 x) { $return(math::isnan(x)); });
    auto isnan64 = to_callable<int>(
        [](f64 x) { $return(math::isnan(x)); });
    
    auto jit = ctx.gen_native_jit();
    
    REQUIRE(jit.get_function(abs32)(-4) == Approx(std::abs(-4)));
    REQUIRE(jit.get_function(abs64)(-5) == Approx(std::abs(-5)));
    
    REQUIRE(jit.get_function(mod32)(7, 2) == Approx(std::fmod(7.0f, 2.0f)));
    REQUIRE(jit.get_function(mod64)(7, 2) == Approx(std::fmod(7.0, 2.0)));
    
    REQUIRE(jit.get_function(remainder32)(7, 2) == Approx(std::remainder(7.0f, 2.0f)));
    REQUIRE(jit.get_function(remainder64)(7, 2) == Approx(std::remainder(7.0, 2.0)));
    
    REQUIRE(jit.get_function(exp32)(5) == Approx(std::exp(5.0f)));
    REQUIRE(jit.get_function(exp64)(5) == Approx(std::exp(5.0)));
    
    REQUIRE(jit.get_function(exp2_32)(5) == Approx(std::exp2(5.0f)));
    REQUIRE(jit.get_function(exp2_64)(5) == Approx(std::exp2(5.0)));
    
    REQUIRE(jit.get_function(log32)(5) == Approx(std::log(5.0f)));
    REQUIRE(jit.get_function(log64)(5) == Approx(std::log(5.0)));
    
    REQUIRE(jit.get_function(log2_32)(5) == Approx(std::log2(5.0f)));
    REQUIRE(jit.get_function(log2_64)(5) == Approx(std::log2(5.0)));
    
    REQUIRE(jit.get_function(log10_32)(5) == Approx(std::log10(5.0f)));
    REQUIRE(jit.get_function(log10_64)(5) == Approx(std::log10(5.0)));
    
    REQUIRE(jit.get_function(pow32)(3.2f, 6.7f) == Approx(std::pow(3.2f, 6.7f)));
    REQUIRE(jit.get_function(pow64)(3.2, 6.7)   == Approx(std::pow(3.2, 6.7)));
    
    REQUIRE(jit.get_function(sqrt32)(5) == Approx(std::sqrt(5.0f)));
    REQUIRE(jit.get_function(sqrt64)(5) == Approx(std::sqrt(5.0)));
    
    REQUIRE(jit.get_function(sin32)(5) == Approx(std::sin(5.0f)));
    REQUIRE(jit.get_function(sin64)(5) == Approx(std::sin(5.0)));
    
    REQUIRE(jit.get_function(cos32)(5) == Approx(std::cos(5.0f)));
    REQUIRE(jit.get_function(cos64)(5) == Approx(std::cos(5.0)));
    
    REQUIRE(jit.get_function(tan32)(5) == Approx(std::tan(5.0f)));
    REQUIRE(jit.get_function(tan64)(5) == Approx(std::tan(5.0)));
    
    REQUIRE(jit.get_function(asin32)(0.675f) == Approx(std::asin(0.675f)));
    REQUIRE(jit.get_function(asin64)(0.675)  == Approx(std::asin(0.675)));
    
    REQUIRE(jit.get_function(acos32)(0.675f) == Approx(std::acos(0.675f)));
    REQUIRE(jit.get_function(acos64)(0.675)  == Approx(std::acos(0.675)));
    
    REQUIRE(jit.get_function(atan32)(0.675f) == Approx(std::atan(0.675f)));
    REQUIRE(jit.get_function(atan64)(0.675)  == Approx(std::atan(0.675)));
    
    REQUIRE(jit.get_function(atan2_32)(3.2f, 6.7f) == Approx(std::atan2(3.2f, 6.7f)));
    REQUIRE(jit.get_function(atan2_64)(3.2, 6.7)   == Approx(std::atan2(3.2, 6.7)));
    
    REQUIRE(jit.get_function(ceil32)(3.2f) == Approx(std::ceil(3.2f)));
    REQUIRE(jit.get_function(ceil64)(3.2)  == Approx(std::ceil(3.2)));
    
    REQUIRE(jit.get_function(floor32)(3.2f) == Approx(std::floor(3.2f)));
    REQUIRE(jit.get_function(floor64)(3.2)  == Approx(std::floor(3.2)));
    
    REQUIRE(jit.get_function(trunc32)(3.2f) == Approx(std::trunc(3.2f)));
    REQUIRE(jit.get_function(trunc64)(3.2)  == Approx(std::trunc(3.2)));
    
    REQUIRE(jit.get_function(round32)(3.2f) == Approx(std::round(3.2f)));
    REQUIRE(jit.get_function(round64)(3.2)  == Approx(std::round(3.2)));
    
    REQUIRE(jit.get_function(isfinite32)(3.2f)    == int(std::isfinite(3.2f)));
    REQUIRE(jit.get_function(isfinite64)(3.2)     == int(std::isfinite(3.2)));
    REQUIRE(jit.get_function(isfinite32)(f32_inf) == int(std::isfinite(f32_inf)));
    REQUIRE(jit.get_function(isfinite64)(f64_inf) == int(std::isfinite(f64_inf)));
    REQUIRE(jit.get_function(isfinite32)(f32_nan) == int(std::isfinite(f32_nan)));
    REQUIRE(jit.get_function(isfinite64)(f64_nan) == int(std::isfinite(f64_nan)));
    
    REQUIRE(jit.get_function(isinf32)(3.2f)    == int(std::isinf(3.2f)));
    REQUIRE(jit.get_function(isinf64)(3.2)     == int(std::isinf(3.2)));
    REQUIRE(jit.get_function(isinf32)(f32_inf) == int(std::isinf(f32_inf)));
    REQUIRE(jit.get_function(isinf64)(f64_inf) == int(std::isinf(f64_inf)));
    REQUIRE(jit.get_function(isinf32)(f32_nan) == int(std::isinf(f32_nan)));
    REQUIRE(jit.get_function(isinf64)(f64_nan) == int(std::isinf(f64_nan)));
    
    REQUIRE(jit.get_function(isnan32)(3.2f)    == int(std::isnan(3.2f)));
    REQUIRE(jit.get_function(isnan64)(3.2)     == int(std::isnan(3.2)));
    REQUIRE(jit.get_function(isnan32)(f32_inf) == int(std::isnan(f32_inf)));
    REQUIRE(jit.get_function(isnan64)(f64_inf) == int(std::isnan(f64_inf)));
    REQUIRE(jit.get_function(isnan32)(f32_nan) == int(std::isnan(f32_nan)));
    REQUIRE(jit.get_function(isnan64)(f64_nan) == int(std::isnan(f64_nan)));
}
