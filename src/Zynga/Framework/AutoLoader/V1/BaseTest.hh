<?hh //strict

namespace Zynga\Framework\AutoLoader\V1;

use Zynga\Framework\AutoLoader\V1\Test\Mock\AutoLoader as MockAutoLoader;
use Zynga\Framework\Environment\CodePath\V1\CodePath;
use Zynga\Framework\Testing\TestCase\V2\Base as TestCase;

class BaseTest extends TestCase {

  public function test_constants(): void {
    $this->assertEquals('\\', MockAutoLoader::NAMESPACE_SEPERATOR);
    $this->assertEquals('/', MockAutoLoader::DIRECTORY_SEPERATOR);
  }

  public function test_basic(): void {
    $obj = new MockAutoLoader();
    $this->assertInstanceOf(MockAutoLoader::class, $obj);
    $this->assertFalse($obj->load('someclass'));
    $this->assertEquals(
      CodePath::getRoot().'/tests/autoloader',
      $obj->getFileSystemRoot(),
    );
  }

  public function test_enableDebug(): void {
    $obj = new MockAutoLoader();
    $this->assertFalse($obj->getDebug());
    $obj->enableDebug();
    $this->assertTrue($obj->getDebug());
    $obj->disableDebug();
    $this->assertFalse($obj->getDebug());
  }

  public function test_debugTarget(): void {

    $obj = new MockAutoLoader();
    $this->assertEquals('stdout', $obj->getDebugTarget());

    $this->assertTrue($obj->setDebugTarget('stdout'));
    $this->assertTrue($obj->setDebugTarget('error_log'));

    $this->assertFalse($obj->setDebugTarget('notvalidtarget'));

    $this->assertEquals('error_log', $obj->getDebugTarget());

  }

  public function test_invalidLoad(): void {

    $obj = new MockAutoLoader();
    $this->assertFalse($obj->load('test_invalid_class'));

  }

  public function test_validLoad(): void {

    $obj = new MockAutoLoader();
    $this->assertTrue($obj->load('test\validClass'));

  }

  public function test_invalidLoad_ClassIsNotInFile(): void {

    $obj = new MockAutoLoader();
    $this->assertFalse($obj->load('test\invalidClass'));

  }

  public function test_register_cycle(): void {

    $obj = new MockAutoLoader();

    // we shouldn't be registered
    $this->assertFalse($obj->unregister());

    // let's register
    $this->assertTrue($obj->register());

    // Now try to do it again, should fail safely.
    $this->assertFalse($obj->register());

    // now take ourselves off the stack.
    $this->assertTrue($obj->unregister());

    // shouldn't be registered, and should safely fail.
    $this->assertFalse($obj->unregister());

  }

}
