#!/ usr / bin / env bash

################################ #
#Update Author : Andy YF Wang #
#Update Date : 2020 / 06 / 16 #
#Ver. : 1.0.0 #
    ################################ #

    ##Get MAC0 via BMC's REST command ## eth0_mac =
        $(busctl get -
              property xyz.openbmc_project.Network / xyz / openbmc_project /
                  network /
                  eth0 xyz.openbmc_project.Network.MACAddress MACAddress |
          sed 's/^...//;s/.$//;s/\://;s/\://;s/\://;s/\://;s/\://') if
            ["${#eth0_mac}" - ne 12];
then eth0_mac = 0 $eth0_mac fi

    ##Get MAC1 via BMC's REST command ##	 eth1_mac =
        $(busctl get -
              property xyz.openbmc_project.Network / xyz / openbmc_project /
                  network /
                  eth1 xyz.openbmc_project.Network.MACAddress MACAddress |
          sed 's/^...//;s/.$//;s/\://;s/\://;s/\://;s/\://;s/\://') if
            ["${#eth1_mac}" - ne 12];
then eth1_mac = 0 $eth1_mac fi

    ##Get PN via BMC's REST command ## pn = $(
        busctl get - property xyz.openbmc_project.Inventory.Manager / xyz /
                         openbmc_project / inventory / system / chassis /
                         motherboard xyz.openbmc_project.Inventory.Decorator
                             .Asset PartNumber |
        sed 's/^...//;s/.$//')

        ##Get SN via BMC's REST command ## sn = $(
            busctl get - property xyz.openbmc_project.Inventory.Manager / xyz /
                             openbmc_project / inventory / system / chassis /
                             motherboard xyz.openbmc_project.Inventory.Decorator
                                 .Asset SerialNumber |
            sed 's/^...//;s/.$//')

            ##Get PrettyName via BMC's REST command ## ptn =
                $(busctl get -
                      property xyz.openbmc_project.Inventory.Manager / xyz /
                          openbmc_project / inventory / system / chassis /
                          motherboard /
                          bmc xyz.openbmc_project.Inventory.Item PrettyName |
                  sed 's/^...//;s/.$//')

                    while[-z "$pn"] ||
                [-z "$sn"] || [-z "$ptn"] do pn = $(
                    busctl get -
                        property xyz.openbmc_project.Inventory.Manager / xyz /
                            openbmc_project / inventory / system / chassis /
                            motherboard xyz.openbmc_project.Inventory.Decorator
                                .Asset PartNumber |
                    sed 's/^...//;s/.$//')

                    sn = $(busctl get -
                               property xyz.openbmc_project.Inventory.Manager /
                                   xyz / openbmc_project / inventory / system /
                                   chassis /
                                   motherboard xyz.openbmc_project.Inventory
                                       .Decorator.Asset SerialNumber |
                           sed 's/^...//;s/.$//')

                        ptn = $(
                            busctl get -
                                property xyz.openbmc_project.Inventory.Manager /
                                    xyz / openbmc_project / inventory / system /
                                    chassis / motherboard /
                                    bmc xyz.openbmc_project.Inventory
                                        .Item PrettyName |
                            sed 's/^...//;s/.$//')

                            if[[-n "$pn"]];
then / usr / bin / env writeEE - p -
    v $pn fi

    if[[-n "$sn"]];
then / usr / bin / env writeEE - s -
    v $sn fi

    if[[-n "$ptn"]];
then / usr / bin / env writeEE - d -
    v $ptn fi

    if[[-n "$eth0_mac"]];
then / usr / bin / env writeEE - m -
    v $eth0_mac fi

    if[[-n "$eth1_mac"]];
then / usr / bin / env writeEE - m -
    v $eth1_mac fi

    ## #Run command to reset BMC’s VPD service## #printf
    "\n > Reset BMC’s VPD service...\n" systemctl stop op -
    vpd - parser.service echo -
    e "\n > Stop op-vpd-parser.service\n " systemctl start op - vpd -
    parser.service echo -
    e "\n > Start op-vpd-parser.service\n "

    done
