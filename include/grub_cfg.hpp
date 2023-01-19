#ifndef __GRUB_CFG_HPP__
#define __GRUB_CFG_HPP__

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace grub
{
    class Entry
    {
    public:
        explicit Entry(const std::string &title, const std::string &kernel, const std::string &initrd, const std::string &options) noexcept;
        Entry(const Entry &other) = default;
        Entry(Entry &&other) noexcept = default;
        Entry &operator=(const Entry &other) = default;
        Entry &operator=(Entry &&other) noexcept = default;
        Entry() = delete;
        ~Entry() = default;
        nlohmann::json to_json() const;

        friend std::ostream &operator<<(std::ostream &os, const Entry &entry);

    private:
        std::string title;
        std::string kernel;
        std::string initrd;
        std::string options;
    };

    std::vector<Entry> get_menu_entries(const std::string &grub_cfg_path);
}

#endif