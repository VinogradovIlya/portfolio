bash ai_door_management_module.sh
mv door_management_fi door_management_files
bash ai_door_management_module.sh
cd door_management_files
mkdir door_configuration
mv *.conf door_configuration
mkdir door_map
mv door_map_1.1 door_map
mkdir door_logs && mv *.log door_logs