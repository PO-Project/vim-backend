#ifndef VIMBACKEND_H_
#define VIMBACKEND_H_

#include <string>
#include <functional>

#include "common-interface/BackendBase.hpp"

namespace backends
{

class VimBackend : public BackendBase
{
public:
    void bind(const std::string &command, std::function<void()> callback, const std::string &helpMessage) noexcept override {}
    void operator()() override;

protected:
    tools::ToolBase *tool;
};

} // namespace backends
#endif
