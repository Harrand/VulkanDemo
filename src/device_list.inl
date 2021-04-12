namespace vkd
{
    DeviceList filter_devices(const DeviceList& devices, std::initializer_list<SuitablePredicate auto> filters)
    {
        DeviceList devs;
        for(const auto& device : devices)
        {
            bool accepted = true;
            for(const auto& filter : filters)
            {
                if(!filter(device))
                {
                    accepted = false;
                    break;
                }
            }
            if(accepted)
            {
                devs.push_back(device);
            }
        }
        return devs;
    }
}