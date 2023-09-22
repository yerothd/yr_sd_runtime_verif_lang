#
# @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
#

# SHOWS THIS Makefile FILE COMMAND STRING IN THE
# CONSOLE AS THEY ARE EXECUTED.
set -x


$(yr_sd_runtime_verif_lang_comp < test_inputs/yr_test_input_1.spec_sd_mealy)


MEALY_MACHINE_NAME=$(cat outputted_SD_MEALY_MACHINE_NAME.txt)


# Replaces file name with prefix 'yr-db-runtime-verif-main-GENERATED'
# with new file prefix 'yr-db-runtime-verif-main'.

GENERATED_FILE_PREFIX="${MEALY_MACHINE_NAME}-GENERATED"

NEW_FILE_FROM_GENERATED_FILE_PREFIX="${MEALY_MACHINE_NAME}"


yerothx-rename-files.sh -o "${GENERATED_FILE_PREFIX}" \
	-n "${NEW_FILE_FROM_GENERATED_FILE_PREFIX}" * 


# Replacing all occurences of string 'yr-db-runtime-verif-main-GENERATED'
# by string 'yr-db-runtime-verif-main'.

yerothx-replace-string.sh -o "${GENERATED_FILE_PREFIX}" \
	-n "${NEW_FILE_FROM_GENERATED_FILE_PREFIX}" "${NEW_FILE_FROM_GENERATED_FILE_PREFIX}".hpp

yerothx-replace-string.sh -o "${GENERATED_FILE_PREFIX}" \
	-n "${NEW_FILE_FROM_GENERATED_FILE_PREFIX}" "${NEW_FILE_FROM_GENERATED_FILE_PREFIX}".cpp

astyle "${NEW_FILE_FROM_GENERATED_FILE_PREFIX}".hpp 

astyle "${NEW_FILE_FROM_GENERATED_FILE_PREFIX}".cpp

