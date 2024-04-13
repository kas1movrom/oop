//
// Created by romka on 13.12.2023.
//

#ifndef CPU_FINAL_CORE_H
#define CPU_FINAL_CORE_H

#include "../../../exe_units/exe_types/alu/include/arithmetic_logic_unit.h"
#include "../../../exe_units/exe_types/fpu/include/floating_point_unit.h"
#include "../../../exe_units/exe_types/bs/include/base_shifter.h"

#include <array>
#include <memory>

namespace cpu {

    class Core {

    private:

        static const std::size_t numberExeUnits = 3;

        std::size_t curInstruction = -1;
        std::array<std::unique_ptr<ExeUnit>, numberExeUnits> units;

    public:

        inline static const std::size_t nPos = std::string::npos;

        Core();

        [[nodiscard]] std::size_t get_current_inst() const;
        Core& set_current_inst(std::size_t instructions);

        std::unique_ptr<ExeUnit>& get_unit(std::size_t index);
    };

}


#endif //CPU_FINAL_CORE_H
