package com.github.fabianmurariu.unsafe

import org.scalatest.BeforeAndAfterAll
import org.scalatest.flatspec.AnyFlatSpec
import org.scalatest.matchers.should.Matchers
import org.scalatestplus.scalacheck.ScalaCheckDrivenPropertyChecks

class GRAPHBLASSpec extends AnyFlatSpec with ScalaCheckDrivenPropertyChecks with Matchers with BeforeAndAfterAll
  with MatrixUtils
  with VectorUtils
  with ApplySpec
  with SemiringSpec
  with ReduceSpec
  {

  behavior of "GrB_Matrix"

    it should "change size when resize is called" in forAll { md: MatrixDimensions =>
      val MatrixDimensions(rows, cols) = md
      val mat = GRBCORE.createMatrix(GRAPHBLAS.booleanType(), rows, cols)
      GRBCORE.nrows(mat) shouldBe rows
      GRBCORE.ncols(mat) shouldBe cols
      GRBCORE.resizeMatrix(mat, cols, rows)
      GRBCORE.nrows(mat) shouldBe cols
      GRBCORE.ncols(mat) shouldBe rows
    }

    testSettersAndGettersMatrix[Boolean](GRAPHBLAS.booleanType())
      {(mat, i, j, value) => GRAPHBLAS.setMatrixElementBoolean(mat, i, j, value) }
      {(mat, i, j) => GRAPHBLAS.getMatrixElementBoolean(mat, i, j).headOption }

    testSettersAndGettersMatrix[Byte](GRAPHBLAS.byteType())
      {(mat, i, j, value) => GRAPHBLAS.setMatrixElementByte(mat, i, j, value) }
      {(mat, i, j) => GRAPHBLAS.getMatrixElementByte(mat, i, j).headOption }

    testSettersAndGettersMatrix[Short](GRAPHBLAS.shortType())
      {(mat, i, j, value) => GRAPHBLAS.setMatrixElementShort(mat, i, j, value) }
      {(mat, i, j) => GRAPHBLAS.getMatrixElementShort(mat, i, j).headOption }

  testSettersAndGettersMatrix[Int](GRAPHBLAS.intType())
    { (mat, i, j, value) => GRAPHBLAS.setMatrixElementInt(mat, i, j, value) }
    { (mat, i, j) => GRAPHBLAS.getMatrixElementInt(mat, i, j).headOption }


    testSettersAndGettersMatrix[Long](GRAPHBLAS.longType())
      {(mat, i, j, value) => GRAPHBLAS.setMatrixElementLong(mat, i, j, value) }
      {(mat, i, j) => GRAPHBLAS.getMatrixElementLong(mat, i, j).headOption }

    testSettersAndGettersMatrix[Float](GRAPHBLAS.floatType())
      {(mat, i, j, value) => GRAPHBLAS.setMatrixElementFloat(mat, i, j, value) }
      {(mat, i, j) => GRAPHBLAS.getMatrixElementFloat(mat, i, j).headOption }

    testSettersAndGettersMatrix[Double](GRAPHBLAS.doubleType())
      {(mat, i, j, value) => GRAPHBLAS.setMatrixElementDouble(mat, i, j, value) }
      {(mat, i, j) => GRAPHBLAS.getMatrixElementDouble(mat, i, j).headOption }

  behavior of "GrB_Vector"

    it should "change size when resize is called" in forAll { (size:VectorDimensions, newSize:VectorDimensions) =>
        val vec = GRBCORE.createVector(GRAPHBLAS.booleanType(), size.size)
        GRBCORE.size(vec) shouldBe size.size
        GRBCORE.resizeVector(vec, newSize.size)
        GRBCORE.size(vec) shouldBe newSize.size
    }

    testSettersAndGettersVector[Boolean](GRAPHBLAS.booleanType())
    {(vec, i, value) => GRAPHBLAS.setVectorElementBoolean(vec, i, value)}
    {(vec, i) => GRAPHBLAS.getVectorElementBoolean(vec, i).headOption}

    testSettersAndGettersVector[Short](GRAPHBLAS.shortType())
      {(vec, i, value) => GRAPHBLAS.setVectorElementShort(vec, i, value)}
      {(vec, i) => GRAPHBLAS.getVectorElementShort(vec, i).headOption}

    testSettersAndGettersVector[Int](GRAPHBLAS.intType())
      {(vec, i, value) => GRAPHBLAS.setVectorElementInt(vec, i, value)}
      {(vec, i) => GRAPHBLAS.getVectorElementInt(vec, i).headOption}

    testSettersAndGettersVector[Long](GRAPHBLAS.longType())
      {(vec, i, value) => GRAPHBLAS.setVectorElementLong(vec, i, value)}
      {(vec, i) => GRAPHBLAS.getVectorElementLong(vec, i).headOption}

    testSettersAndGettersVector[Float](GRAPHBLAS.floatType())
      {(vec, i, value) => GRAPHBLAS.setVectorElementFloat(vec, i, value)}
      {(vec, i) => GRAPHBLAS.getVectorElementFloat(vec, i).headOption}

    testSettersAndGettersVector[Double](GRAPHBLAS.doubleType())
      {(vec, i, value) => GRAPHBLAS.setVectorElementDouble(vec, i, value)}
      {(vec, i) => GRAPHBLAS.getVectorElementDouble(vec, i).headOption}

  override protected def beforeAll(): Unit = {
    GRBCORE.initNonBlocking()
  }

  override protected def afterAll(): Unit = {
//    GRBCORE.grbWait()
//    GRBCORE.grbFinalize()
  }
}

