package com.github.fabianmurariu.unsafe;

import org.junit.Before;
import org.junit.Test;

import java.nio.Buffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import static org.junit.Assert.assertTrue;

public class SimpleJavaExample {

    private static final int NODE_COUNT = 7;
    private static final int RELATIONSHIP_COUNT = 12;

    @Before
    public void setUp() {
        GRBCORE.initNonBlocking();
    }

    /**
     * https://fosdem.org/2020/schedule/event/graphblas/attachments/slides/4132/export/events/attachments/graphblas/slides/4132/graphblas_introduction.pdf
     * slide: 27
     */
    @Test
    public void simpleNxM() {
        // "Buffer" == address to matrix
        Buffer matrix = GRBCORE.createMatrix(GRAPHBLAS.doubleType(), NODE_COUNT, NODE_COUNT);

        long[] colIds = {0, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6};
        long[] rowIds = {3, 0, 3, 5, 6, 0, 6, 1, 6, 2, 4, 1};
        double[] m_values = new double[RELATIONSHIP_COUNT];
        Arrays.fill(m_values, 1);

        GRAPHBLAS.buildMatrixFromTuplesDouble(matrix, rowIds, colIds, m_values, RELATIONSHIP_COUNT, GRAPHBLAS.firstBinaryOpDouble());

        // present -> value present in first entry of array
        assertTrue(GRAPHBLAS.getMatrixElementBoolean(matrix, 0, 3)[0]);
        // if not present -> no value in the result array
        assertTrue(GRAPHBLAS.getMatrixElementBoolean(matrix, 0, 0).length == 0);


        Buffer vector = GRBCORE.createVector(GRAPHBLAS.doubleType(), NODE_COUNT);
        long[] ids = {3, 5};
        double[] v_values = {1, 1};
        GRAPHBLAS.buildVectorFromTuplesDouble(vector, ids, v_values, 2, GRAPHBLAS.firstBinaryOpDouble());

        // !! only a binary op and no whole monoid for mul (.. as also mentioned in the C-API)
        Buffer semiRing = GRBCORE.createSemiring(GRBMONOID.plusMonoidDouble(), GRAPHBLAS.timesBinaryOpDouble());

        Buffer result = GRBCORE.createVector(GRAPHBLAS.doubleType(), NODE_COUNT);

        int outCode = GRBOPSMAT.vxm(result, null, null, semiRing, vector, matrix, null);

        assert (outCode == GRBCORE.GrB_SUCCESS);

        System.out.println("adjacency matrix: \n" + doubleMatrixToString(matrix, NODE_COUNT));

        System.out.println("input vector: \n" + doubleVectorToString(vector, NODE_COUNT));
        System.out.println("result: \n" + doubleVectorToString(result, NODE_COUNT));
    }

    private String doubleVectorToString(Buffer result, int nodeCount) {
        List<String> values = new ArrayList<>();

        for (int i = 0; i < nodeCount; i++) {
            double[] value = GRAPHBLAS.getVectorElementDouble(result, i);
            if (value.length != 0) {
                values.add(Double.toString(value[0]));
            } else {
                values.add("?");
            }
        }

        return values.stream().collect(Collectors.joining(","));
    }

    private String doubleMatrixToString(Buffer result, int nodeCount) {
        List<List<String>> values = new ArrayList<>();
        int maxValueLength = 1;

        for (int row = 0; row < nodeCount; row++) {
            List<String> rowString = new ArrayList<>();
            values.add(rowString);

            for (int col = 0; col < nodeCount; col++) {
                double[] optional_value = GRAPHBLAS.getMatrixElementDouble(result, row, col);
                if (optional_value.length != 0) {
                    String v = Double.toString(optional_value[0]);
                    maxValueLength = Math.max(maxValueLength, v.length());
                    rowString.add(v);
                } else {
                    rowString.add("?");
                }
            }
        }

        int finalMaxValueLength = maxValueLength;
        return values.stream()
                .map(row -> row.stream()
                        .map(v -> String.format("%1$" + finalMaxValueLength + "s", v))
                        .collect(Collectors.joining(",")))
                .collect(Collectors.joining(System.lineSeparator()));
    }
}
