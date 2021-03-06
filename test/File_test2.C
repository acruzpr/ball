// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////
#include <BALL/SYSTEM/file.h>
#include <sys/types.h>
#include <sys/stat.h>
///////////////////////////

using namespace BALL;
using namespace std;


START_TEST(File)


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

String source_name(BALL_TEST_DATA_PATH(../File_test2.C));

CHECK(bool operator == (const File& file) const throw())
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
/* TODO: we can't copy files!
	File f1(f);
	TEST_EQUAL(f1 == f, true)	
*/
	file.copyTo("XXX");
	File f2("XXX");
	TEST_EQUAL(f2 == f, false)	
	TEST_EQUAL(file.getSize(), 100)
RESULT

CHECK(bool operator != (const File& file) const throw())
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
	/* TODO: we can't copy files!
	File f1(f);
	TEST_EQUAL(f1 != f, false)	
	*/
	file.copyTo("XXX");
	File f2("XXX");
	TEST_EQUAL(f2 != f, true)	
	TEST_EQUAL(file.getSize(), 100)
RESULT

CHECK(static bool isAccessible(String name))
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
	TEST_EQUAL(f.isAccessible(BALL_TEST_DATA_PATH(File_test2.txt)), true)
	f.remove("XXX");
	TEST_EQUAL(f.isAccessible("XXX"), false)
RESULT

CHECK(bool isAccessible() const throw())
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
	TEST_EQUAL(f.isAccessible(), true)
	file.copyTo("XXZ");

	File f1("XXZ");
	f1.remove();
	TEST_EQUAL(f1.isAccessible(), false)
RESULT

CHECK(bool isCanonized() const)
	File f0(BALL_TEST_DATA_PATH(../../test/data/File_test2.txt));
	TEST_EQUAL(f0.isValid(), true)
	TEST_EQUAL(f0.isCanonized(), true)

	File f2(BALL_TEST_DATA_PATH(/File_test2.txt));
	TEST_EQUAL(f2.isValid(), true)
	TEST_EQUAL(f2.isCanonized(), true)

	File f4(BALL_TEST_DATA_PATH(../data/File_test2.txt));
	TEST_EQUAL(f4.isValid(), true)
	TEST_EQUAL(f4.isCanonized(), true)

	File f5(BALL_TEST_DATA_PATH(.././data/File_test2.txt));
	TEST_EQUAL(f5.isValid(), true)
	TEST_EQUAL(f5.isCanonized(), true)

	File f6(BALL_TEST_DATA_PATH(File_test2.txt));
	TEST_EQUAL(f6.isValid(), true)
	TEST_EQUAL(f6.isCanonized(), true)

	File x;
	x.setName("this_file_should_not_exists");
	TEST_EXCEPTION(Exception::FileNotFound, x.isCanonized())
RESULT

CHECK(static bool isReadable(String name))
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
	TEST_EQUAL(f.isReadable(source_name), true)	

	TEST_EXCEPTION(Exception::FileNotFound, File::isReadable("this_file_should_not_exists"))
RESULT

CHECK(bool isReadable() const)
	File f2(source_name);
	TEST_EQUAL(f2.isReadable(), true)

	File x;
	TEST_EXCEPTION(Exception::FileNotFound, x.isReadable())
RESULT

CHECK(static bool isWritable(String name))
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
	TEST_EQUAL(f.isWritable(source_name), true)	

	TEST_EXCEPTION(Exception::FileNotFound, File::isWritable("this_file_should_not_exists"))
RESULT

CHECK(bool isWritable() const)
	File f2(source_name);
	TEST_EQUAL(f2.isWritable(), true)	

	File x;
	TEST_EXCEPTION(Exception::FileNotFound, x.isWritable())
RESULT

CHECK(static bool isExecutable(String name))
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
#ifndef BALL_COMPILER_MSVC
	TEST_EQUAL(f.isExecutable(BALL_TEST_DATA_PATH(File_test2.txt)), true)
#endif
	TEST_EQUAL(f.isExecutable(source_name), false)	

	TEST_EXCEPTION(Exception::FileNotFound, File::isExecutable("this_file_should_not_exists"))
RESULT

CHECK(bool isExecutable() const)
#ifndef BALL_COMPILER_MSVC
	File f1(BALL_TEST_DATA_PATH(File_test2.txt));
	TEST_EQUAL(f1.isExecutable(), true)	
#endif
	File f2(source_name);
	TEST_EQUAL(f2.isExecutable(), false)	
RESULT

CHECK(bool isValid() const throw())
	File f;
	TEST_EQUAL(f.isValid(), false)	

	File f1;
	TEST_EXCEPTION(Exception::FileNotFound, f1.open("XXY"))
	TEST_EQUAL(f1.isValid(), false)	

	File f2(source_name);
	TEST_EQUAL(f2.isValid(), true)	
	f2.close();
	TEST_EQUAL(f2.isValid(), true)	
RESULT

CHECK(bool isOpen() const throw())
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
	TEST_EQUAL(f.isOpen(), true)	
	File f2;
	TEST_EQUAL(f2.isOpen(), false)	
	f2.open(source_name);
	TEST_EQUAL(f2.isOpen(), true)	
	f2.close();
	TEST_EQUAL(f2.isOpen(), false)	
RESULT

CHECK(bool isClosed() const throw())
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	const File& f  = file;
	TEST_EQUAL(f.isClosed(), false)	
	File f2;
	TEST_EQUAL(f2.isClosed(), true)	
	f2.open(source_name);
	TEST_EQUAL(f2.isClosed(), false)	
	f2.close();
	TEST_EQUAL(f2.isClosed(), true)	
RESULT

String filename;
CHECK(std::fstream& getFileStream())
	NEW_TMP_FILE(filename);
	File new_file(filename, std::ios::out);
	File  file(BALL_TEST_DATA_PATH(File_test2.txt));
	new_file.getFileStream() << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
	new_file.close();
	TEST_FILE(filename.c_str(), BALL_TEST_DATA_PATH(File_test2.txt))

	File x;
	x.getFileStream();
RESULT

CHECK(void clear() throw())
	File file(filename);
	file.clear();
	TEST_EQUAL(file.getName(), "")
RESULT

CHECK(bool reopen(File::OpenMode open_mode))
	File file(filename);
	TEST_EQUAL(file.reopen(), true)
	file.setName("this_file_should_not_exists");
	TEST_EQUAL(file.getName(), "this_file_should_not_exists")
	TEST_EXCEPTION(Exception::FileNotFound, file.reopen())
RESULT

CHECK(void setName(const String& name) throw())
	File file;
	file.setName(filename);
	file.setName("this_file_should_not_exists");
RESULT

CHECK(const String& getOriginalName() const)
	File file;
	TEST_EQUAL(file.getOriginalName(), "")
	File file2(String("file:")+argv[0]);
	TEST_EQUAL(file2.getOriginalName(), String("file:")+argv[0])
	TEST_EQUAL(file2.getName(), argv[0])
RESULT

CHECK(TransformationManager& getTransformationManager())
	File file;
	TEST_EQUAL(file.getTransformationManager().findTransformation("ftp://"), "")
RESULT

CHECK(const TransformationManager& getTransformationManager() const)
	File file;
	file.getTransformationManager().registerTransformation("xxx://", "ls");
RESULT

CHECK(static void disableTransformation(Transformation transformation))
	File::disableTransformation(File::TRANSFORMATION__URL);
	TEST_EQUAL(File::isTransformationEnabled(File::TRANSFORMATION__URL), false)
RESULT

CHECK(static void enableTransformation(Transformation transformation))
	File::enableTransformation(File::TRANSFORMATION__URL);
	TEST_EQUAL(File::isTransformationEnabled(File::TRANSFORMATION__URL), true)
RESULT

CHECK(static void registerTransformation(const String& pattern, const String& exec))
	File::registerTransformation("yyy://", "ls");
RESULT

CHECK(static void unregisterTransformation(const String& pattern))
	File::unregisterTransformation("yyy://");
	File::unregisterTransformation("xxx://");
	File::unregisterTransformation("zzz://");
RESULT

CHECK(static bool isTransformationEnabled(Transformation transformation))
	TEST_EQUAL(File::isTransformationEnabled(File::TRANSFORMATION__URL), true)
RESULT

// ============================================================
// other classes
// ============================================================

// TransformationManager

TransformationManager* m_ptr = 0;
CHECK(TransformationManager())
  m_ptr = new TransformationManager;
RESULT

CHECK(~TransformationManager())
  delete m_ptr;
RESULT

CHECK(String findTransformation(const String& name) const)
	TransformationManager f;
	TEST_EQUAL(f.findTransformation(""), "")
	TEST_EQUAL(f.findTransformation("asddasd"), "")
	TEST_EQUAL(f.findTransformation("ftp://"), "")
RESULT

CHECK(void registerTransformation(const String& pattern, const String& command))
	TransformationManager f;
	f.registerTransformation("asdddasd", "addd");
	TEST_EQUAL(f.findTransformation("asdddasd"), "addd")
RESULT

CHECK(String transform(const String& name))
	TransformationManager f;
	TEST_EQUAL(f.transform(""), "")
	TEST_EQUAL(f.transform("asdd"), "")
	f.registerTransformation("blabla:", "asd");
	TEST_EQUAL(f.transform("blabla"), "")
	TEST_EQUAL(f.transform("blabla:"), "asd");
	f.registerTransformation("my1:", "%s");
	TEST_EQUAL(f.transform("my1:filename.ext"), "my1:filename.ext")
	f.registerTransformation("my2:%s", "name.txt");
	TEST_EQUAL(f.transform("my2:%s"), "name.txt")
	f.registerTransformation("my3:", "%f");
	TEST_EQUAL(f.transform("my3:filename.ext"), "my3:filename")
	f.registerTransformation("my3:", "%f[bla]");
	TEST_EQUAL(f.transform("my3:filename.ext"), "my3:filename")
	TEST_EQUAL(f.transform("my3:filename.bla"), "my3:filename")
	String PS = FileSystem::PATH_SEPARATOR;
	f.registerTransformation("my4:", "%b");
	TEST_EQUAL(f.transform("my4:"+PS+"some_path"+PS+"filename.ext"), "filename")
	f.registerTransformation("my5:", "%p");
	TEST_EQUAL(f.transform("my5:"+PS+"some_path"+PS+"filename.ext"), "my5:"+PS+"some_path"+PS)
	f.registerTransformation("my6:", "%t");
	String result = f.transform("my6:asddasd");
	TEST_EQUAL(result !="", true )
	TEST_EQUAL(result.size(), 12 )
	TEST_EQUAL(result[0], '_')
	TEST_EQUAL(File::isAccessible(result), false)
RESULT

CHECK(void unregisterTransformation(const String& pattern))
	TransformationManager f;
	f.registerTransformation("asdddasd", "addd");
	f.unregisterTransformation("asdddasd");
	TEST_EQUAL(f.findTransformation("asdddasd"), "")
RESULT

File::CannotWrite* cw_ptr = 0;
CHECK(CannotWrite(const char* file, int line, const String& filename) throw())	
	cw_ptr = new File::CannotWrite("asdf", 1234, "filename");
	TEST_NOT_EQUAL(cw_ptr, 0)
RESULT

CHECK(String getFilename() const throw())
	TEST_EQUAL(cw_ptr->getFilename(), "filename")
RESULT

CHECK(~CannotWrite() throw())
	delete cw_ptr;
RESULT


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
