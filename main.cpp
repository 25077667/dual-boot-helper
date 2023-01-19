#include <grub_cfg.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <grub.cfg path>\n";
        return 1;
    }

    const auto &entries = grub::get_menu_entries(argv[1]);
    std::for_each(entries.begin(), entries.end(), [](const auto &entry)
                  { static size_t counter_ = 0;
                   std::cout << "Entry " << counter_++  << ": " << entry; });

    return 0;
}