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
    // Use std::transform to print entries with indexing
    std::transform(entries.begin(),
                   entries.end(),
                   std::ostream_iterator<grub::Entry>(std::cout),
                   [](const auto &entry)
                   { return entry; });

    return 0;
}