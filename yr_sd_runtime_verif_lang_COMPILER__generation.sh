#
# @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
#

USAGE="Usage: $(basename $0) <-i INPUT_FILE> [-o OUTPUT_FILE]"


if [ $# -lt 1 ]; then
  echo "$USAGE"
fi

inputfileFlag=
outputfileFlag=

while getopts 'i:o:' OPTION
do
  case $OPTION in
    i)	inputfileFlag=1
      	ival="$OPTARG"
	;;
    o)	outputfileFlag=1
      	oval="$OPTARG"
	;;
    ?)	printf "$USAGE" >&2
        exit 1
	;;
  esac
done
shift $(($OPTIND - 1))



if [ ! $inputfileFlag ]; then
	printf "$USAGE\n"
	exit 2
else
	INPUT_SD_MEALY_FILE=${ival}
	echo "|input file: --- ${INPUT_SD_MEALY_FILE} --- |"
fi


if [ $outputfileFlag ]; then
	OUTPUT_SOURCE_CODE_FILE=${oval}
	echo "|output file: --- ${OUTPUT_SOURCE_CODE_FILE} --- |"
fi



# SHOWS THIS Makefile FILE COMMAND STRING IN THE
# CONSOLE AS THEY ARE EXECUTED.
set -x


$(yr_sd_runtime_verif_lang_comp < ${INPUT_SD_MEALY_FILE})


MEALY_MACHINE_NAME=$(cat outputted_SD_MEALY_MACHINE_NAME.txt)

# Replaces file name with prefix '${MEALY_MACHINE_NAME}-GENERATED'
# with new file prefix '${MEALY_MACHINE_NAME}'.

GENERATED_FILE_PREFIX="${MEALY_MACHINE_NAME}-GENERATED"

NEW_FILE_FROM_GENERATED_FILE_PREFIX="${MEALY_MACHINE_NAME}"


if [ $outputfileFlag ]; then
	NEW_FILE_FROM_GENERATED_FILE_PREFIX="${OUTPUT_SOURCE_CODE_FILE}"
fi


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

