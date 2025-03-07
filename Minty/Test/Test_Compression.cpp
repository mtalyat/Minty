#include "Test_Compression.h"
#include "Minty.h"

void test_Compression(Test& _test)
{
	CATEGORY(Compression)
	{
		// ~3k bytes of text
		String text = ""
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit.Nullam eget pulvinar justo, id luctus justo.Aliquam vitae aliquet dui.Sed dictum ligula ut justo dictum, vel tincidunt lectus feugiat.Aliquam sit amet varius felis, vitae elementum tellus.Mauris mattis est ut mi maximus sodales.Praesent in pharetra neque, vitae accumsan nisi.Vestibulum tortor tortor, maximus eu nisl sollicitudin, fermentum tempor dui.Quisque nec finibus risus.Vestibulum vel leo ut metus sagittis iaculis vitae ut ante.Proin sed maximus mi.Cras vel metus consequat, molestie libero vitae, pretium ligula.Cras eleifend metus ut libero vestibulum pretium.Aenean elit magna, blandit id tempus vitae, tempor id magna.Sed vel semper magna.Vestibulum efficitur et arcu quis ultrices.Phasellus vel viverra nisi. "
			"Aliquam malesuada mi non sagittis dapibus.Vestibulum a ante vitae odio pulvinar maximus.Duis ligula enim, fermentum vel tellus sit amet, mollis lacinia turpis.Proin neque mi, dapibus ac erat eu, pulvinar tincidunt est.Ut facilisis dolor ligula, sed feugiat nunc scelerisque eu.Curabitur sodales sagittis massa, tincidunt luctus nulla maximus at.Duis viverra consequat aliquet.Proin nulla neque, pellentesque sit amet consequat dapibus, molestie nec justo.Vivamus purus erat, ullamcorper in leo sit amet, ornare imperdiet libero.Nam ut lacus vitae felis fringilla sagittis.Fusce molestie euismod ligula, sed bibendum urna tempus placerat.Phasellus et ante ante. "
			"Aenean imperdiet mollis orci nec auctor.Suspendisse porta justo ligula, nec semper neque mollis sit amet.Etiam ac erat nisl.Suspendisse fermentum orci non quam bibendum, in laoreet arcu gravida.Donec ut libero id orci lobortis fringilla.Duis at ultricies libero, vitae ultricies ante.Proin posuere tempor odio sed cursus.Aliquam erat volutpat.Nam lacinia a felis quis dignissim.Etiam felis ipsum, placerat sit amet ex eget, rutrum maximus risus. "
			"Quisque id efficitur risus, nec finibus libero.Morbi porttitor dui tristique quam dictum malesuada.Vestibulum lobortis libero eu venenatis tempor.Nam rutrum nisl felis, sit amet facilisis velit pellentesque molestie.Fusce viverra sed leo eu auctor.Fusce vestibulum rutrum nunc ultrices laoreet.In ac lorem et quam pharetra posuere.Nunc consectetur felis ac velit semper, a elementum ipsum tincidunt.Aenean cursus quam sed pellentesque suscipit.Donec porttitor orci in lorem mollis feugiat.Nam a rhoncus massa.Nunc condimentum in nunc in sagittis.Vivamus euismod eu eros eget luctus.Quisque efficitur placerat dui, sit amet semper magna lobortis in. "
			"Quisque lacinia nisl mauris, nec semper urna cursus eu.Suspendisse potenti.Aenean viverra metus sit amet metus ullamcorper, ac iaculis dui semper.Sed congue in ante vel gravida.Praesent porttitor mauris ac ultricies vehicula.Mauris vel varius nisi.Aliquam diam lectus, scelerisque id pellentesque cursus, commodo nec erat.Integer dignissim nulla non eros rhoncus tempor.Phasellus scelerisque porta venenatis.";

		TEST("Compress Bound")
		{
			// get size of compressed string
			ULong bound = compress_bound(text.get_size());

			// compress the string, and compare
			void* stringData = text.get_data();
			ULong stringSize = text.get_size();
			Char buffer[KB * 4];
			memset(buffer, 0, KB * 4 * sizeof(Char));
			ULong bufferSize = KB * 4;

			EXPECT_TRUE(compress(buffer, bufferSize, stringData, stringSize));
			EXPECT_TRUE(bufferSize <= bound);
		}

		TEST("Compress")
		{
			// compress the string, and compare
			void* stringData = text.get_data();
			ULong stringSize = text.get_size();
			Char buffer[KB * 4];
			memset(buffer, 0, KB * 4 * sizeof(Char));
			ULong bufferSize = KB * 4;

			EXPECT_TRUE(compress(buffer, bufferSize, stringData, stringSize));
			EXPECT_FAIL(compress(nullptr, bufferSize, stringData, stringSize));
			EXPECT_FAIL(compress(buffer, bufferSize, nullptr, stringSize));
		}

		TEST("Uncompress")
		{
			// compress the string
			void* stringData = text.get_data();
			ULong stringSize = text.get_size();
			Char buffer[KB * 4];
			memset(buffer, 0, KB * 4 * sizeof(Char));
			ULong bufferSize = KB * 4;

			EXPECT_TRUE(compress(buffer, bufferSize, stringData, stringSize));

			// uncompress the string
			Char buffer2[KB * 4];
			memset(buffer2, 0, KB * 4 * sizeof(Char));
			ULong bufferSize2 = KB * 4;

			EXPECT_TRUE(uncompress(buffer2, bufferSize2, buffer, bufferSize));

			String text2 = String(static_cast<Char const*>(buffer2));

			// we know it was successful if the strings are the same
			EXPECT_TRUE(text == text2);
		}
	}
}
