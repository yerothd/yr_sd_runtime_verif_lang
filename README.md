
# AUTHOR: XAVIER NOUMBISSI NOUNDOU (yeroth.d at gmail.com).


# MIT SOFTWARE LICENSED


# HOW TO BUILD THIS PROJECT

Run bash script 'build_yr_sd_runtime_verig_lang.sh'.


# HOW TO GENERATE C++ FILES for yr-db-runtime-verif FROM A SPECIFICATION FILE

yr_sd_runtime_verif_lang_comp < yr_sd_runtime_verif.sd_mealy


# HERE is a sample state diagram mealy machine SPECIFICATION

yr_sd_mealy_automaton_spec yr_test_MISSING_department
{
 START_STATE(d):NOT_IN_PRE(YR_ASSET, departements_produits.nom_departement_produit)
  -> / 'select.departements_produits'->
   FINAL_STATE(e):IN_POST(YR_ASSET, stocks.nom_departement_produit).
}

