using PowerModelsCompiled

function count_to_ten()
    count = zero(Int32)
    while count < 10
        count = increment32(count)
    end
end

count_to_ten()

# c_load_grid(Base.unsafe_convert(Cstring,"/Users/kbhardwaj6/SSE/donti/pmbe/build/case5.m"))

# output_json = c_solve_power_flow(Base.unsafe_convert(Cstring,"/Users/kbhardwaj6/SSE/donti/pmbe/build/case5.m"))

# println(output_json)