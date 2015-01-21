// This is a comment
// uncomment the line below if you want to write a filterscript
//#define FILTERSCRIPT

#include <a_samp>
#include <icmd>
#include <ibits>

#if defined FILTERSCRIPT

public OnFilterScriptInit()
{
	print("\n--------------------------------------");
	print(" Blank Filterscript by your name here");
	print("--------------------------------------\n");
	return 1;
}

public OnFilterScriptExit()
{
	return 1;
}

#else

main()
{
	print("\n----------------------------------");
	print(" Blank Gamemode by your name here");
	print("----------------------------------\n");
}

#endif

public OnGameModeInit()
{
	// Don't use these lines if it's a filterscript
	SetGameModeText("Blank Script");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	return 1;
}

new bit4: admin <MAX_PLAYERS>;
new bit1: adminTrabalhando <MAX_PLAYERS>;

public Listeners(playerid, params[])
{
	get_cmd_noparams(trabalhar)
	{
	    //seta a booleana do admin trabalhando para a inversa do valor antigo.
		setBit1(adminTrabalhando, playerid, !getBit1(adminTrabalhando, playerid));
		return 1;
	}
	get_cmd_params(matar)
	{
	    if (!params[0]) SendClientMessage(playerid, -1, "Syntax: /matar [id]");

        //lendo valor da variável admin do playerid, para saber se ele tem nível..
        if (!getBit4(admin, playerid)) SendClientMessage(playerid, -1, "Você não é um admin.");

        //Lendo valor da var adminTrabalhando, para saber se ele está em modo de trabalho.
        if (!getBit1(adminTrabalhando, playerid)) SendClientMessage(playerid, -1, "Você não está em modo trabalho.");

        SetPlayerHealth(strval(params), 0.0);
		return 1;
	}
	get_cmd_params(admin)
	{
        if (!params[0]) SendClientMessage(playerid, -1, "Syntax: /admin [value]");

	    if (0 > strval(params) > 5) SendClientMessage(playerid, -1, "Nível inválido.");

	    //setando valor da variável para a quantidade digitada
	    setBit4(admin, playerid, strval(params));

	    SendClientMessage(playerid, -1, "Você alterou seu nível de admin.");
	}
	return 0;
}
