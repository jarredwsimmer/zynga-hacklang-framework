<?hh // strict

namespace Zynga\Framework\Database\V2\Interfaces;

use Zynga\Framework\Database\V2\Interfaces\DriverInterface;

interface TransactionInterface {

  /**
   * Creates a database specific transaction object.
   * @param DriverInterface $driver
   * @return TransactionInterface
   */
  public function __construct(DriverInterface $driver);

  /**
   * Starts a transaction on your database.
   * @return bool
   */
  public function begin(): bool;

  /**
   * Commits the currently active transaction.
   * @return bool
   */
  public function commit(): bool;

  /**
   * Rolls the current transaction back on the database.
   * @return bool
   */
  public function rollback(): bool;

}
