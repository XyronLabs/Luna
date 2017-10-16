function map(n, orig_min, orig_max, new_min, new_max)
    return ( (n - orig_min) * (new_max - new_min) ) / ( (orig_max - orig_min) + new_min )
end