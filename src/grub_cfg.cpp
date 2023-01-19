#include <grub_cfg.hpp>
#include <fstream>
#include <iostream>

namespace detail
{
    std::string get_string_between(const std::string &str, const std::string &start, const std::string &end)
    {
        const auto start_pos = str.find(start);
        if (start_pos == std::string::npos)
            return "";
        const auto end_pos = str.find(end, start_pos + start.length());
        if (end_pos == std::string::npos)
            return "";
        return str.substr(start_pos + start.length(), end_pos - start_pos - start.length());
    }

    std::string get_title(const std::string &line)
    {
        return get_string_between(line, "'", "'");
    }

    std::pair<std::string, std::string> parse_kernel_line(const std::string &line)
    {
        // linux   /vmlinuz-linux root=UUID=165a8258-9699-4f6c-a086-bde7f9e42ee8 rw  loglevel=3 quiet
        const auto &kernel = std::string("/") + get_string_between(line, "/", " ");
        const auto &options = get_string_between(line + '$', kernel + ' ', "$");
        return {kernel, options};
    }

    std::string get_initrd(const std::string &line)
    {
        // initrd  /initramfs-linux.img
        return std::string("/") + get_string_between(line + '$', "/", "$");
    }

    // Parse single menuentry from grub.cfg ifstream file
    grub::Entry parse_menuentry(std::ifstream &grub_cfg, const std::string &title)
    {
        std::string line;
        // Read until kernel info line
        while (std::getline(grub_cfg, line))
        {
            if (line.find("\tlinux") != std::string::npos)
                break;
            else if (line.find("\twindows") != std::string::npos)
                break;
        }
        const auto &[kernel, options] = parse_kernel_line(line);
        // Read until initrd info line
        while (std::getline(grub_cfg, line))
        {
            if (line.find("initrd") != std::string::npos)
                break;
        }
        // initrd  /initramfs-linux.img
        const auto &initrd = get_initrd(line);
        // Read until menuentry close '}' or EOF
        while (std::getline(grub_cfg, line))
        {
            if (line.find("}") != std::string::npos)
                break;
        }
        return grub::Entry(title, kernel, initrd, options);
    }
}

grub::Entry::Entry(const std::string &title, const std::string &kernel, const std::string &initrd, const std::string &options) noexcept
    : title(title), kernel(kernel), initrd(initrd), options(options)
{
}

nlohmann::json grub::Entry::to_json() const
{
    nlohmann::json j;
    j["title"] = title;
    j["kernel"] = kernel;
    j["initrd"] = initrd;
    j["options"] = options;
    return j;
}

std::ostream &grub::operator<<(std::ostream &os, const grub::Entry &entry)
{
    return os << entry.to_json() << "\n";
}

std::vector<grub::Entry> grub::get_menu_entries(const std::string &grub_cfg_path)
{
    std::vector<grub::Entry> entries;
    std::ifstream grub_cfg(grub_cfg_path);
    std::string line;
    while (std::getline(grub_cfg, line))
    {
        // Title is between the first and second single-quotes in the first line
        if (line.find("menuentry") == 0)
        {
            entries.emplace_back(detail::parse_menuentry(grub_cfg, detail::get_title(line)));
        }
        // submenus are not supported now
#ifdef DEBUG
        std::clog << line << "\n";
#endif
    }
    return entries;
}