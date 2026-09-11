#pragma once

/** @file shared_resource_api.h
 * @brief 共享资源插件接口：调用 acquire() 时返回一个 std::shared_ptr，
 *        供其他插件共享使用。
 *
 * 典型用法：宿主加载资源插件 -> init() -> acquire() 取得 shared_ptr ->
 * 注入到其他插件的初始化参数中；多个消费者插件共享同一份资源实例，
 * 生命周期由 shared_ptr 引用计数管理，最后持有者释放时销毁。
 *
 * 注意：资源对象必须独立于插件实例存活（不要返回指向插件成员的裸视图），
 * 否则插件实例销毁后 shared_ptr 仍然有效但指向的内容会悬空。
 */

#include <memory>
#include <string>

#include <Pluma/Pluma.hpp>

namespace plane {

/// 共享资源基类。资源插件实现具体资源，消费者按约定转换为具体类型使用。
class SharedResource {
   public:
    virtual ~SharedResource() = default;

    /// 资源名称，用于日志与冲突排查。
    virtual std::string name() const = 0;
};

/// 共享资源插件初始化参数。
struct SharedResourceConfig {
    std::string model_path;  ///< 资源文件/模型地址（可空）
    bool use_gpu = false;    ///< 是否使用加速设备
};

/// 共享资源插件：init 准备资源，acquire 返回可被多个插件共享的 shared_ptr。
class SharedResourcePlugin {
   public:
    virtual ~SharedResourcePlugin() = default;

    /// 初始化资源；成功返回 true，失败返回 false。
    virtual bool init(const SharedResourceConfig& config) = 0;

    /// 返回共享资源；无可用资源时返回空 shared_ptr。
    /// 调用方可长期持有返回值：资源在所有持有者释放后销毁。
    virtual std::shared_ptr<SharedResource> acquire() = 0;
};

PLUMA_PROVIDER_HEADER(SharedResourcePlugin);

}  // namespace plane
