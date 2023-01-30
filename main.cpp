#include <grub_cfg.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <grub.cfg path>\n";
        return 1;
    }
    const std::string grub_cfg_path = argv[1];

    const auto &entries = grub::get_menu_entries(grub_cfg_path);
    std::for_each(entries.begin(), entries.end(), [](const auto &entry)
                  { static size_t counter_ = 0;
                   std::cout << "Entry " << counter_++  << ": " << entry; });

    size_t index = 0;
    std::cout << "\nSelect new default boot enty: ";
    std::cin >> index;
    if (index >= entries.size())
    {
        std::cerr << "Invalid index\n";
        return 1;
    }

    std::cout << "Selected entry: " << entries[index];

    if (grub::save_default_entry(index, grub_cfg_path))
        std::cout << "Done\n";
    else
        std::cerr << "Failed to save default entry\n";

    return 0;
}