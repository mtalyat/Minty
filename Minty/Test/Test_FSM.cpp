#include "Test_FSM.h"
#include "Minty.h"

void test_FSM(Test& _test)
{
	CATEGORY(FSM)
	{
		TEST("Default Constructor")
		{
			FSM fsm;
			EXPECT_EQUAL(fsm.get_current_state_id(), INVALID_ID);
			EXPECT_EQUAL(fsm.get_starting_state_id(), INVALID_ID);
		}

		TEST("Get Scope")
		{
			FSM fsm;
			EXPECT_SUCCESS(fsm.get_scope());
		}

		TEST("Get Scope Const")
		{
			FSM const fsm;
			EXPECT_SUCCESS(fsm.get_scope());
		}

		TEST("Get State")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.get_state(INVALID_ID));
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.get_state(stateId));
		}

		TEST("Get State Const")
		{
			FSM fsm;
			FSM const& fsmConst = fsm;
			EXPECT_FAILURE(fsmConst.get_state(INVALID_ID));
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsmConst.get_state(stateId));
		}

		TEST("Set Current State")
		{
			FSM fsm;
			UUID stateId0 = fsm.create_state("Test0");
			UUID stateId1 = fsm.create_state("Test1");
			EXPECT_SUCCESS(fsm.set_current_state(stateId0));
			EXPECT_EQUAL(fsm.get_current_state_id(), stateId0);
			EXPECT_SUCCESS(fsm.set_current_state(stateId1));
			EXPECT_EQUAL(fsm.get_current_state_id(), stateId1);
			EXPECT_FAILURE(fsm.set_current_state(INVALID_ID));
		}

		TEST("Get Current State ID")
		{
			FSM fsm;
			EXPECT_EQUAL(fsm.get_current_state_id(), INVALID_ID);
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.set_current_state(stateId));
			EXPECT_EQUAL(fsm.get_current_state_id(), stateId);
		}

		TEST("Get Current State")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.get_current_state());
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.set_current_state(stateId));
			EXPECT_SUCCESS(fsm.get_current_state());
		}

		TEST("Get Current State Const")
		{
			FSM fsm;
			FSM const& fsmConst = fsm;
			EXPECT_FAILURE(fsmConst.get_current_state());
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.set_current_state(stateId));
			EXPECT_SUCCESS(fsmConst.get_current_state());
		}

		TEST("Has Current State")
		{
			FSM fsm;
			EXPECT_FALSE(fsm.has_current_state());
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.set_current_state(stateId));
			EXPECT_TRUE(fsm.has_current_state());
		}

		TEST("Set Starting State")
		{
			FSM fsm;
			UUID stateId0 = fsm.create_state("Test0");
			UUID stateId1 = fsm.create_state("Test1");
			EXPECT_SUCCESS(fsm.set_starting_state(stateId0));
			EXPECT_EQUAL(fsm.get_starting_state_id(), stateId0);
			EXPECT_SUCCESS(fsm.set_starting_state(stateId1));
			EXPECT_EQUAL(fsm.get_starting_state_id(), stateId1);
			EXPECT_FAILURE(fsm.set_starting_state(INVALID_ID));
		}

		TEST("Get Starting State ID")
		{
			FSM fsm;
			EXPECT_EQUAL(fsm.get_starting_state_id(), INVALID_ID);
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.set_starting_state(stateId));
			EXPECT_EQUAL(fsm.get_starting_state_id(), stateId);
		}

		TEST("Get Starting State")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.get_starting_state());
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.set_starting_state(stateId));
			EXPECT_SUCCESS(fsm.get_starting_state());
		}

		TEST("Get Starting State Const")
		{
			FSM fsm;
			FSM const& fsmConst = fsm;
			EXPECT_FAILURE(fsmConst.get_starting_state());
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.set_starting_state(stateId));
			EXPECT_SUCCESS(fsmConst.get_starting_state());
		}

		TEST("Has Starting State")
		{
			FSM fsm;
			EXPECT_FALSE(fsm.has_starting_state());
			UUID stateId = fsm.create_state("Test");
			EXPECT_SUCCESS(fsm.set_starting_state(stateId));
			EXPECT_TRUE(fsm.has_starting_state());
		}

		TEST("Set Variable")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.set_variable(INVALID_ID, 0));
			UUID varId = fsm.create_variable("Test");
			EXPECT_SUCCESS(fsm.set_variable(varId, 0));
			EXPECT_EQUAL(fsm.get_variable(varId), 0);
			EXPECT_SUCCESS(fsm.set_variable(varId, 1));
			EXPECT_EQUAL(fsm.get_variable(varId), 1);
		}

		TEST("Get Variable")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.get_variable(INVALID_ID));
			UUID varId = fsm.create_variable("Test");
			EXPECT_SUCCESS(fsm.set_variable(varId, 0));
			EXPECT_EQUAL(fsm.get_variable(varId), 0);
		}

		TEST("Get Variable Name")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.get_variable_name(INVALID_ID));
			UUID varId = fsm.create_variable("Test");
			EXPECT_EQUAL(fsm.get_variable_name(varId), "Test");
		}

		TEST("Get State Name")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.get_state_name(INVALID_ID));
			UUID stateId = fsm.create_state("Test");
			EXPECT_EQUAL(fsm.get_state_name(stateId), "Test");
		}

		TEST("Create State")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.create_state(""));
			EXPECT_NOT_EQUAL(fsm.create_state("Test"), INVALID_ID);
		}

		TEST("Add State")
		{
			FSM fsm;
			State state;
			EXPECT_FAILURE(fsm.add_state("", state));
			EXPECT_NOT_EQUAL(fsm.add_state("Test", state), INVALID_ID);
		}

		TEST("Create Variable")
		{
			FSM fsm;
			EXPECT_FAILURE(fsm.create_variable(""));
			EXPECT_NOT_EQUAL(fsm.create_variable("Test"), INVALID_ID);
		}

		TEST("Find Variable")
		{
			FSM fsm;
			EXPECT_EQUAL(fsm.find_variable(""), INVALID_ID);
			UUID varId = fsm.create_variable("Test");
			EXPECT_EQUAL(fsm.find_variable("Test"), varId);
		}

		TEST("Evaluate")
		{
			FSM fsm;
			
			// evaluate without any states
			EXPECT_FALSE(fsm.evaluate());

			// add variables
			UUID xId = fsm.create_variable("x");
			UUID yId = fsm.create_variable("y");

			// add states
			UUID BLstateId = fsm.create_state("BL");
			UUID BRstateId = fsm.create_state("BR");
			UUID TLstateId = fsm.create_state("TL");
			UUID TRstateId = fsm.create_state("TR");

			// add transitions
			State& BLstate = fsm.get_state(BLstateId);
			State& BRstate = fsm.get_state(BRstateId);
			State& TLstate = fsm.get_state(TLstateId);
			State& TRstate = fsm.get_state(TRstateId);

			BLstate.add_transition(Transition(BRstateId, {
				{ xId, Conditional::Equal, 1 }
				}));
			BLstate.add_transition(Transition(TLstateId, {
				{ yId, Conditional::Equal, 1 }
				}));
			BRstate.add_transition(Transition(BLstateId, {
				{ xId, Conditional::Equal, 0 }
				}));
			BRstate.add_transition(Transition(TRstateId, {
				{yId, Conditional::Equal, 1 }
				}));

		}
	}
}
