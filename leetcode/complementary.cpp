    int findComplement(int num) 
    {
        auto mask = reinterpret_cast<uint32_t&>(num);
        mask |= (mask >> 1);
        mask |= (mask >> 2);
        mask |= (mask >> 4);
        mask |= (mask >> 8);
        mask |= (mask >> 16);    
        return ~num & mask;
    }
    
